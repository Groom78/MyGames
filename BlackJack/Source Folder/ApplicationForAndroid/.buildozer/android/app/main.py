import os
import random
import sys
from kivy.app import App
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.button import Button
from kivy.uix.label import Label
from kivy.uix.image import Image
from kivy.clock import Clock
from kivy.core.window import Window
from kivy.uix.anchorlayout import AnchorLayout
from kivy.storage.jsonstore import JsonStore

from Scripts.tool_box import ChipRain, try_percent, create_card_image, pulse_button_green, pulse_button_yellow, ensure_stats_file
from Scripts.sfx import SFX
from Scripts.game import Game
from Scripts.UI import UI
from Scripts.languages import Translator

delays_between_actions = 0.6

def get_base_path():
    if getattr(sys, 'frozen', False):
        return sys._MEIPASS
    return os.path.abspath(os.path.dirname(__file__))

class MainWidget(BoxLayout):
    def __init__(self, translator=None, chip_rain_obj = None, **kwargs):
        base_dir = get_base_path()
        self.main_path = base_dir
        audio_path = os.path.join(self.main_path, "Assets", "Audio")
        self.chip_rain = chip_rain_obj
        self.translator = translator
        self.saves = dict()

        self.button_color_green = (0.0, 0.4, 0.0, 1)
        self.button_color_yellow = (1, 0.8, 0.2, 1)
        self.button_color_red = (1, 0.2, 0.2, 1)
        self.funny_sounds = True
        self.fun_rate = 5

        self.store = JsonStore(os.path.join(self.main_path, "Saves", "save.json"))
        self.saves["win_count"] = self.store.get("wins")["value"]
        self.saves["draw_count"] = self.store.get("draws")["value"]
        self.saves["loss_count"] = self.store.get("losses")["value"]
        self.saves["balance"] = self.store.get("balance")["value"]
        self.saves["bet_amount"] = self.store.get("bet_amount")["value"]
        self.saves["hit_count"] = self.store.get("hit_count")["value"]
        self.saves["stand_count"] = self.store.get("stand_count")["value"]
        self.saves["double_count"] = self.store.get("double_count")["value"]
        self.saves["surrender_count"] = self.store.get("surrender_count")["value"]
        self.saves["bust_count"] = self.store.get("bust_count")["value"]
        self.saves["five_card_charlie_count"] = self.store.get("five_card_charlie_count")["value"]
        self.saves["dealer_blackjack_count"] = self.store.get("dealer_blackjack_count")["value"]
        self.saves["fivecardcharlie"] = self.store.get("fivecardcharlie")["value"]
        self.saves["hitsonsoft17"] = self.store.get("hitsonsoft17")["value"]
        self.saves["language_preference"] = self.store.get("language_preference")["value"]
        self.saves["blackjack_count"] = self.store.get("blackjack_count")["value"]
        self.saves["special_announcements"] = self.store.get("special_announcements")["value"]
        self.saves["total_earnings"] = self.store.get("total_earnings")["value"]
        self.saves["largest_win"] = self.store.get("largest_win")["value"]
        self.saves["total_bets"] = self.store.get("total_bets")["value"]
        self.ui_bet = self.saves["bet_amount"]

        self.sfx = SFX(audio_path = audio_path, play_welcome_sound = self.saves["special_announcements"])
        self.game = Game(deck_count=6)
        self.is_a_blackjack = False
        self.pause = False
        super().__init__(**kwargs)
        self.orientation = 'vertical'
        self.card_scale = 0.26
        
        self.use_five_card_charlie_next_round = True
        self.saves["five_card_charlie"] = True
        self.saves["dealer_hits_on_soft_17"] = False
        self.use_dealer_hits_on_soft_17_next_round = False

        def stop_pop_ups_if_playing(instance, touch):
            self.sfx.stop_tutorial_ups_if_playing()
            self.ui.stop_stats_tab_if_playing()
        
        Window.bind(on_touch_down=stop_pop_ups_if_playing)

        self.player_cards = []
        self.dealer_cards = []

        self.dealer_layout = BoxLayout(
            orientation='vertical',
            size_hint=(1, 0.35),
            padding=[0, 450, 0, 0]
        )
        self.add_widget(self.dealer_layout)

        self.player_layout = BoxLayout(
            orientation='vertical',
            size_hint=(1, 0.35),
            padding=[0, 0, 0, 50]
        )
        self.add_widget(self.player_layout)

        self.extra_button_layout = BoxLayout(
            orientation='vertical',
            size_hint=(1, 0.1),
            padding=[0, 0, 0, 0]
        )
        self.add_widget(self.extra_button_layout)

        self.info_label = Label(text="", size_hint=(1, 0.1), font_size='22sp')
        self.add_widget(self.info_label)

        self.buttons_layout = BoxLayout(
            orientation='horizontal',
            size_hint=(1, 0.3)
        )

        self.hit_button = Button(
            text=self.translator.get("hit"),
            font_size='22sp',
            background_normal='',
            background_color=self.button_color_green,
            size_hint=(0.5, 0.7)
        )
        self.translator.items["hit_button"] = self.hit_button
        self.stand_button = Button(
            text=self.translator.get("stand"),
            font_size="22sp",
            background_normal='',
            background_color=self.button_color_green,
            size_hint=(0.5, 0.7)
        )
        self.translator.items["stand_button"] = self.stand_button
        self.surrender_button = Button(
            text=self.translator.get("surrender"),
            font_size="9sp",
            background_normal='',
            background_color=self.button_color_red,
            size_hint=(None, None),
            size=(120, 80)
        )
        self.translator.items["surrender_button"] = self.surrender_button
        self.double_button = Button(
            text=self.translator.get("2x"),
            font_size="18sp",
            background_normal='',
            background_color= self.button_color_yellow,
            size_hint=(None, None),
            size=(120, 80)
        )
        self.translator.items["double_button"] = self.double_button

        pulse_button_green(self.hit_button)
        pulse_button_yellow(self.double_button)
        self.hit_button.bind(on_release=self.hit_button_pressed)
        self.stand_button.bind(on_release=self.stand_button_pressed)
        self.double_button.bind(on_release=self.double_button_pressed)
        self.surrender_button.bind(on_release=self.surrender_button_pressed)
        self.add_widget(self.buttons_layout)

    def update_stats(self):
        self.store.put("wins", value=self.saves["win_count"])
        self.store.put("draws", value=self.saves["draw_count"])
        self.store.put("losses", value=self.saves["loss_count"])
        self.store.put("balance", value=self.saves["balance"])
        self.store.put("bet_amount", value=self.saves["bet_amount"])
        self.store.put("fivecardcharlie", value=self.saves["five_card_charlie"])
        self.store.put("hitsonsoft17", value=self.saves["dealer_hits_on_soft_17"])
        self.store.put("hit_count", value=self.saves["hit_count"])
        self.store.put("double_count", value=self.saves["double_count"])
        self.store.put("surrender_count", value=self.saves["surrender_count"])
        self.store.put("bust_count", value=self.saves["bust_count"])
        self.store.put("five_card_charlie_count", value=self.saves["five_card_charlie_count"])
        self.store.put("dealer_blackjack_count", value=self.saves["dealer_blackjack_count"])
        self.store.put("blackjack_count", value=self.saves["blackjack_count"])
        self.store.put("special_announcements", value=self.saves["special_announcements"])
        self.store.put("total_earnings", value=self.saves["total_earnings"])
        self.store.put("largest_win", value=self.saves["largest_win"])
        self.store.put("total_bets", value=self.saves["total_bets"])
        
    def start_game(self):
        self.saves["bet_amount"] = self.ui_bet
        self.info_label.text = ""
        if self.saves["balance"] < self.saves["bet_amount"]:
            if self.saves["balance"] >= 1:
                self.saves["bet_amount"] = self.saves["balance"]
                self.info_label.text = self.translator.get("allin")+"!"
            else:
                self.saves["bet_amount"] = 0
                self.info_label.text = self.translator.get("nomorechips")+"!"
        self.saves["balance"] -= self.saves["bet_amount"]
        self.saves["total_bets"] += self.saves["bet_amount"]
        self.update_balance_label()
        self.player_cards = []
        self.dealer_cards = []
        self.game.is_over = False
        self.game.result = 0
        self.game.player.hand.cards.clear()
        self.game.dealer.hand.cards.clear()

        delay = delays_between_actions
        Clock.schedule_once(lambda dt: self.deal_card_to_player(True), delay)
        Clock.schedule_once(lambda dt: self.deal_card_to_dealer(True), delay*2)
        Clock.schedule_once(lambda dt: self.deal_card_to_player(True), delay*3)
        Clock.schedule_once(lambda dt: self.deal_card_to_dealer(False), delay*4)
        Clock.schedule_once(lambda dt: self.check_blackjack(), delay*5)

    def check_blackjack(self):
        player_score = self.game.player.hand.calculate_score()
        if player_score == 21:
            self.reveal_dealer_card(1)
            self.sfx.play_flip_sound()
            Clock.schedule_once(lambda dt: self.check_blackjack_dealer(), delays_between_actions)
        else:
            self.buttons_layout.add_widget(self.stand_button)
            self.buttons_layout.add_widget(self.hit_button)
            if not self.game.is_over and len(self.game.player.hand.cards) == 2 and len(self.game.dealer.hand.cards) == 2:
                self.extra_button_layout.add_widget(self.surrender_button)   
                self.extra_button_layout.add_widget(self.double_button)

    def check_blackjack_dealer(self):
        dealer_score = self.game.dealer.hand.calculate_score()
        if dealer_score == 21:
            self.saves["dealer_blackjack_count"] += 1
            self.game.is_over = True
            self.game.result = 0
            self.update_display()
        else:
            self.game.is_over = True
            self.game.result = 2
            self.update_display()

    def deal_card_to_player(self, face_up=True):
        card = self.game.deck.deal_card()
        self.game.player.hand.add_card(card)
        self.player_cards.append((card, face_up))
        self.sfx.play_flip_sound()
        self.update_display()

    def deal_card_to_dealer(self, face_up=True):
        card = self.game.deck.deal_card()
        self.game.dealer.hand.add_card(card)
        self.dealer_cards.append((card, face_up))
        self.sfx.play_flip_sound()
        self.update_display()

    def reveal_dealer_card(self, index):
        card, _ = self.dealer_cards[index]
        self.dealer_cards[index] = (card, True)
        self.update_display()

    def update_display(self, bust=False):
        self.dealer_layout.clear_widgets()
        self.player_layout.clear_widgets()
        self.extra_button_layout.clear_widgets()

        def build_hand(cards, is_dealer):
            total_cards = len(cards)
            
            card_width_px = int(Window.width * self.card_scale)
            card_height_px = int(card_width_px * 1.4)
            
            if total_cards <= 3:
                overlap = 0
                layout_width = total_cards * card_width_px
            else:
                overlap = 0.4 * card_width_px  
                layout_width = card_width_px + (total_cards - 1) * (card_width_px - overlap)
            
            layout = BoxLayout(
                orientation='horizontal',
                size_hint=(None, None),
                width=layout_width,
                height=card_height_px,
                spacing=-overlap if total_cards > 3 else 0
            )
            
            for i, (card, face_up) in enumerate(cards):
                if not self.game.is_over:
                    if face_up:
                        layout.add_widget(create_card_image(card = card, main_path = self.main_path, card_scale = self.card_scale))
                    else:
                        back_path = os.path.join(get_base_path(), "Assets", "Images", "Cards", "jpg", "BackSide.jpg")
                        layout.add_widget(create_card_image(card = None, custom_path=back_path, main_path = self.main_path, card_scale = self.card_scale))
                else:
                    if is_dealer and bust and not face_up:
                        back_path = os.path.join(get_base_path(), "Assets", "Images", "Cards", "jpg", "BackSide.jpg")
                        layout.add_widget(create_card_image(card = None, custom_path=back_path, main_path = self.main_path, card_scale = self.card_scale))
                    else:
                        layout.add_widget(create_card_image(card = card, main_path = self.main_path, card_scale = self.card_scale))
            
            anchor = AnchorLayout(anchor_x='center', anchor_y='bottom', size_hint=(1, 1))
            anchor.add_widget(layout)
            return anchor

        self.dealer_layout.add_widget(build_hand(self.dealer_cards, True))
        self.player_layout.add_widget(build_hand(self.player_cards, False))
        
        if self.game.is_over:
            if self.game.result == 2:
                self.chip_rain.start(type="bj")
                self.info_label.text = self.translator.get("blackjack") + "!"
                if self.saves["special_announcements"]:
                    self.sfx.play_blackjack_announce()
                    Clock.schedule_once(lambda dt: self.sfx.play_blackjack_sound(), delays_between_actions * 1.5)
                else:
                    self.sfx.play_blackjack_sound()
                self.saves["balance"] += self.saves["bet_amount"] * 2.5
                self.saves["largest_win"] = max(self.saves["largest_win"], self.saves["bet_amount"] * 1.5)
                self.saves["total_earnings"] += self.saves["bet_amount"] * 1.5
                self.saves["win_count"] += 1
                self.saves["blackjack_count"] += 1
            elif self.game.result == 1:
                self.chip_rain.start()
                self.info_label.text = self.translator.get("win") + "!"
                self.saves["balance"] += self.saves["bet_amount"] * 2
                self.saves["largest_win"] = max(self.saves["largest_win"], self.saves["bet_amount"])
                self.saves["total_earnings"] += self.saves["bet_amount"]
                if self.funny_sounds and try_percent(self.fun_rate) and self.saves["special_announcements"]:
                    self.sfx.play_game_ending_sound("funny_win")
                else:
                    self.sfx.play_game_ending_sound("win")
                self.saves["win_count"] += 1
            elif self.game.result == -1:
                self.info_label.text = self.translator.get("lose") + "!"
                if self.funny_sounds and try_percent(self.fun_rate) and self.saves["special_announcements"]:
                    self.sfx.play_game_ending_sound("funny_lose")
                else:
                    self.sfx.play_game_ending_sound("lose")
                self.saves["loss_count"] += 1
            else:
                self.info_label.text = self.translator.get("draw") + "!"
                self.saves["balance"] += self.saves["bet_amount"]
                if self.funny_sounds and try_percent(self.fun_rate) and self.saves["special_announcements"]:
                    self.sfx.play_game_ending_sound("funny_draw")
                else:
                    self.sfx.play_game_ending_sound("draw")
                self.saves["draw_count"] += 1
            self.show_restart_button()
            self.update_stats()
            self.update_balance_label()

    def double_button_pressed(self, instance):
        if not self.game.is_over and not self.pause and self.saves["balance"] >= self.saves["bet_amount"]:
            self.saves["double_count"] += 1
            self.info_label.text = ""
            self.pause = True
            self.buttons_layout.clear_widgets()
            self.extra_button_layout.clear_widgets()
            self.info_label.text = self.translator.get("doubledown") + "!"
            self.saves["balance"] -= self.saves["bet_amount"]
            self.saves["total_bets"] += self.saves["bet_amount"]
            self.saves["bet_amount"] *= 2
            self.update_balance_label()
            Clock.schedule_once(lambda dt: self.player_hit_action(None,double=True), delays_between_actions)

    def surrender_button_pressed(self, instance):
        if not self.game.is_over and not self.pause:
            self.saves["surrender_count"] += 1
            self.pause = True
            self.buttons_layout.clear_widgets()
            self.extra_button_layout.clear_widgets()
            self.info_label.text = self.translator.get("surrender") + "!"
            self.saves["balance"] += self.saves["bet_amount"] / 2
            self.update_balance_label()
            Clock.schedule_once(lambda dt: self.show_restart_button(), delays_between_actions / 2)

    def hit_button_pressed(self, instance):
        if not self.game.is_over and not self.pause:
            self.saves["hit_count"] += 1
            self.info_label.text = ""
            self.pause = True
            self.buttons_layout.clear_widgets()
            self.extra_button_layout.clear_widgets()
            Clock.schedule_once(self.player_hit_action, delays_between_actions)

    def player_hit_action(self, dt, double = False):
        self.deal_card_to_player(True)
        score = self.game.player.hand.calculate_score()
        if double:
            if score > 21:
                self.game.is_over = True
                self.game.result = -1
                self.update_display(bust = True)
            else:
                Clock.schedule_once(lambda dt: self.reveal_dealer_card(1), delays_between_actions)
                Clock.schedule_once(lambda dt: self.sfx.play_flip_sound(), delays_between_actions)
                Clock.schedule_once(self.dealer_hit_action, delays_between_actions * 2)
        elif self.saves["five_card_charlie"] and len(self.game.player.hand.cards) == 5 and score <= 21:
            self.saves["five_card_charlie_count"] += 1
            self.game.is_over = True
            self.game.result = 1
            self.update_display(bust = True)
        elif score > 21:
            self.saves["bust_count"] += 1
            self.game.is_over = True
            self.game.result = -1
            self.update_display(bust = True)
        elif score == 21:
            self.pause = False
            Clock.schedule_once(lambda dt: self.stand_button_pressed(None), delays_between_actions)
        else:
            self.pause = False
            self.buttons_layout.add_widget(self.stand_button)
            self.buttons_layout.add_widget(self.hit_button)

    def stand_button_pressed(self, instance):
        if not self.game.is_over and not self.pause:
            self.saves["stand_count"] += 1
            self.info_label.text = ""
            self.pause = True
            self.buttons_layout.clear_widgets()
            self.extra_button_layout.clear_widgets()
            Clock.schedule_once(lambda dt: self.reveal_dealer_card(1), 0.1)
            self.sfx.play_flip_sound()
            Clock.schedule_once(self.dealer_hit_action, delays_between_actions + 0.1)

    def dealer_hit_action(self, dt):
        if self.game.is_over:
            return
        dealer_score = self.game.dealer.hand.calculate_score()
        if dealer_score < 17 or (dealer_score == 17 and self.saves["dealer_hits_on_soft_17"] and self.game.dealer.hand.has_an_ace()):
            #   Delaer hits
            self.deal_card_to_dealer(True)
            Clock.schedule_once(self.dealer_hit_action, delays_between_actions)
            return
        if dealer_score > 21:
            # Dealer busts
            self.game.result = 1
        else:
            # Dealer stands
            if dealer_score == 21 and len(self.game.dealer.hand.cards) == 2:
                self.saves["dealer_blackjack_count"] += 1
            player_score = self.game.player.hand.calculate_score()
            if dealer_score > player_score:
                self.game.result = -1
            elif dealer_score < player_score:
                self.game.result = 1
            else:
                self.game.result = 0
        self.game.is_over = True
        self.pause = False
        self.update_display()

    def show_restart_button(self):
        self.buttons_layout.clear_widgets()
        self.extra_button_layout.clear_widgets()
        restart_button = Button(
            text=self.translator.get("rematch"),
            font_size="22sp",
            background_normal='',
            background_color=self.button_color_green,
            size_hint=(1, 0.7)
        )
        self.translator.items["restart_button"] = restart_button
        restart_button.bind(on_release=self.on_restart)
        self.buttons_layout.add_widget(restart_button)

    def on_restart(self, instance):
        self.info_label.text = ""
        self.sfx.play_shuffle_sound()
        self.pause = False
        self.chip_rain.stop()
        self.buttons_layout.clear_widgets()
        self.extra_button_layout.clear_widgets()
        self.saves["five_card_charlie"] = self.use_five_card_charlie_next_round
        self.saves["dealer_hits_on_soft_17"] = self.use_dealer_hits_on_soft_17_next_round

        self.hit_button = Button(
            text=self.translator.get("hit"),
            font_size="22sp",
            background_normal='',
            background_color=self.button_color_green,
            size_hint=(0.5, 0.7)
        )
        self.translator.items["hit_button2"] = self.hit_button
        self.stand_button = Button(
            text=self.translator.get("stand"),
            font_size="22sp",
            background_normal='',
            background_color=self.button_color_green,
            size_hint=(0.5, 0.7)
        )
        self.translator.items["stand_button2"] = self.stand_button
        pulse_button_green(self.hit_button)
        self.hit_button.bind(on_release=self.hit_button_pressed)
        self.stand_button.bind(on_release=self.stand_button_pressed)
        self.start_game()

    def toggle_charlie(self, checkbox, value):
        self.use_five_card_charlie_next_round = value

    def toggle_soft_17(self, checkbox, value):
        self.use_dealer_hits_on_soft_17_next_round = value
    
    def toggle_spec_anno(self, checkbox, value):
        self.saves["special_announcements"] = value

    def update_balance_label(self):
        self.balance_label.text = f"${self.saves['balance']}"

class BlackjackApp(App):
    def build(self):
        root = FloatLayout()
        base_dir = os.path.dirname(__file__)

        if not os.path.exists(os.path.join(base_dir, "Saves")):
            os.makedirs(os.path.join(base_dir, "Saves"))
        ensure_stats_file(base_dir)
        chip_layer = FloatLayout(size_hint=(1, 1), pos_hint={'x': 0, 'y': 0})
        chip_rain = ChipRain(chip_layer, main_dir=base_dir)
        self.store = JsonStore(os.path.join(base_dir, "Saves", "save.json"))
        current_languege = self.store.get("language_preference")["value"]
        translator = Translator(base_dir, current_languege)
        main_layout = MainWidget(translator = translator, chip_rain_obj =  chip_rain, size_hint=(1, 1), pos_hint={'x': 0, 'y': 0})
        ui = UI(main_layout = main_layout, main_dir = base_dir, translator = translator, root = root)
        main_layout.ui = ui

        root.add_widget(ui.get_background())
        root.add_widget(main_layout)
        root.add_widget(chip_layer)
        main_layout.chip_layer = chip_layer

        root.add_widget(ui.get_right_top_panel())
        root.add_widget(ui.get_left_top_panel())
        ui.get_stats_tab()
        ui.stop_stats_tab_if_playing()

        main_layout.update_stats()
        main_layout.start_game()
        return root

if __name__ == "__main__":
    BlackjackApp().run()
