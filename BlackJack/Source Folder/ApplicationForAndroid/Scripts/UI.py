import os
from kivy.uix.label import Label
from kivy.uix.slider import Slider
from kivy.uix.button import Button
from kivy.uix.checkbox import CheckBox
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.anchorlayout import AnchorLayout
from kivy.uix.image import Image
from kivy.uix.textinput import TextInput
from kivy.uix.spinner import Spinner
from kivy.uix.widget import Widget

class UI:
    def __init__(self, main_layout=None, main_dir=None, translator=None, root=None):
        self.root = root
        self.translator = translator
        self.main_layout = main_layout
        self.main_dir = main_dir
        self.right_panel_active = False

    def get_background(self):
        bg_path = os.path.join(self.main_dir, "Assets", "Images", "Others", "BackGround.jpg")

        return Image(
            source=bg_path,
            size_hint=(1, 1),
            pos_hint={'x': 0, 'y': 0},
            fit_mode='fill'
        )

    def get_right_top_panel(self):
        # Sağ paneli oluşturuyoruz.
        self.right_panel = BoxLayout(
            orientation='vertical',
            size_hint=(None, None),
            size=(240, 470),
            padding=10,
            spacing=35,
            pos_hint={'right': 0.95, 'top': 0.95}
        )

        # 1) ÜST KUTU: Ayarlar butonunun sabit kalması için ayrı bir kutu oluşturuyoruz.
        top_box = BoxLayout(
            orientation='horizontal',
            size_hint=(None, None),
            size=(300, 100)
        )

        spacer = Widget()
        top_box.add_widget(spacer)

        # Butonu pos_hint olmadan ekleyin
        self.settings_button = Button(
            size_hint=(None, None),
            size=(120, 120),
            background_normal=os.path.join(self.main_dir, "Assets", "Images", "Others", "settings_icon.png"),
            background_down=os.path.join(self.main_dir, "Assets", "Images", "Others", "settings_icon.png"),
            background_color=(1, 1, 1, 1)
        )
        self.settings_button.bind(on_release=self.toggle_settings)
        top_box.add_widget(self.settings_button)

        # 2) ALT KUTU: Ayar butonuna tıklanınca eklenecek diğer widget’lar burada yer alacak.
        self.toggle_box = BoxLayout(
            orientation='vertical',
            size_hint=(None, None),
            size=(330, 360),  # Kalan alan; ihtiyaca göre ayarlanabilir
            spacing=35
        )

        # Sağ panelde önce sabit buton (top_box) sonra toggle_box yer alır.
        self.right_panel.add_widget(top_box)
        self.right_panel.add_widget(self.toggle_box)

        # Diğer widget’ların oluşturulması

        # Volume Slider
        self.volume_slider = Slider(
            min=0,
            max=1,
            value=self.main_layout.sfx.volume_level,
            size_hint=(None, None),
            width=300,
            height=10,
            orientation='horizontal'
        )
        self.volume_slider.bind(value=self.main_layout.sfx.on_volume_change)

        # Tutorial Button
        self.tutorial_button = Button(
            text="?",
            font_size=45,
            size_hint=(None, None),
            size=(60, 60),
            background_normal='',
            background_color=(0.2, 0.2, 0.5, 1)
        )
        self.tutorial_button.bind(on_release=lambda x: self.main_layout.sfx.play_tutorial())

        # Checkbox 1
        self.checkbox_layout1 = BoxLayout(
            orientation='horizontal',
            size_hint=(None, None),
            size=(220, 30),
            spacing=6
        )
        charlie_checkbox = CheckBox(active=self.main_layout.use_five_card_charlie_next_round)
        charlie_checkbox.bind(active=self.main_layout.toggle_charlie)
        checkbox_label = Label(
            text=self.translator.get("fivecardcharlie"),
            font_size=17,
            size_hint=(None, None),
            size=(160, 30)
        )
        self.translator.items["fivecardcharlie"] = checkbox_label
        self.checkbox_layout1.add_widget(charlie_checkbox)
        self.checkbox_layout1.add_widget(checkbox_label)

        # Checkbox 2
        self.checkbox_layout2 = BoxLayout(
            orientation='horizontal',
            size_hint=(None, None),
            size=(220, 30),
            spacing=6
        )
        soft_17_checkbox = CheckBox(active=self.main_layout.use_dealer_hits_on_soft_17_next_round)
        soft_17_checkbox.bind(active=self.main_layout.toggle_soft_17)
        checkbox_label = Label(
            text=self.translator.get("hitsonsoft17"),
            font_size=17,
            size_hint=(None, None),
            size=(160, 30)
        )
        self.translator.items["hitsonsoft17"] = checkbox_label
        self.checkbox_layout2.add_widget(soft_17_checkbox)
        self.checkbox_layout2.add_widget(checkbox_label)

        # Checkbox 3
        self.checkbox_layout3 = BoxLayout(
            orientation='horizontal',
            size_hint=(None, None),
            size=(220, 30),
            spacing=6
        )
        spec_anno_checkbox = CheckBox(active=self.main_layout.saves["special_announcements"])
        spec_anno_checkbox.bind(active=self.main_layout.toggle_spec_anno)
        checkbox_label = Label(
            text=self.translator.get("specialannounces"),
            font_size=17,
            size_hint=(None, None),
            size=(160, 30)
        )
        self.translator.items["specialannounces"] = checkbox_label
        self.checkbox_layout3.add_widget(spec_anno_checkbox)
        self.checkbox_layout3.add_widget(checkbox_label)

        # Dil seçici (Spinner)
        self.spinner = Spinner(
            text=self.translator.current_language,
            values=self.translator.choices,
            font_size=20,
            size_hint=(None, None),
            size=(250, 50)
        )
        self.spinner.bind(text=self.translator.on_language_change)

        right_anchor = FloatLayout(size_hint=(1, 1))
        self.right_panel.pos_hint = {'right': 0.95, 'top': 0.97}
        right_anchor.add_widget(self.right_panel)

        return right_anchor

    def get_left_top_panel(self):
        left_anchor = AnchorLayout(
            anchor_x='left',
            anchor_y='top',
            size_hint=(1, 1),
            pos_hint={'left': 0.95, 'top': 0.97}
        )

        left_panel = BoxLayout(
            orientation='vertical',
            size_hint=(None, None),
            size=(260, 240),
            padding=10,
            spacing=10
        )

        balance_layout = BoxLayout(
            orientation='horizontal',
            size_hint=(None, None),
            size=(260, 60),
            spacing=8
        )

        coin_container = AnchorLayout(
            anchor_x='center',
            anchor_y='center',
            size_hint=(None, None),
            size=(48, 60)
        )
        coin_icon = Image(
            source=os.path.join(self.main_dir, "Assets", "Images", "Others", "coinbj.png"),
            size_hint=(None, None),
            size=(48, 48)
        )
        coin_container.add_widget(coin_icon)

        self.main_layout.balance_label = Label(
            text=f"{self.main_layout.saves['balance']}",
            font_size=44,
            color=(1, 1, 0, 1),
            size_hint=(None, None),
            size=(200, 60),
            text_size=(200, 60),
            halign='left',
            valign='middle'
        )
        self.main_layout.balance_label.bind(size=self.main_layout.balance_label.setter('text_size'))

        stats_button = Button(
            text='',
            size_hint=(None, None),
            size=(70, 70),
            background_normal=os.path.join(self.main_dir, "Assets", "Images", "Others", "stats.png"),
            background_down=os.path.join(self.main_dir, "Assets", "Images", "Others", "stats.png"),
            border=(0, 0, 0, 0)
        )

        stats_button.bind(on_release=lambda x: self.get_stats_tab())

        balance_layout.add_widget(coin_container)
        balance_layout.add_widget(self.main_layout.balance_label)

        bet_title = Label(
            text=self.translator.get("betamount") + ":",
            font_size=20,
            size_hint=(None, None),
            halign='left',
            valign='center',
            size=(150, 30),
            text_size=(150, 20)
        )
        self.translator.items["betamount"] = bet_title
        bet_title.bind(size=bet_title.setter('text_size'))

        self.bet_input = TextInput(
            text=str(self.main_layout.saves["bet_amount"]),
            font_size=30,
            input_filter='int',
            input_type='number',
            multiline=False,
            size_hint=(None, None),
            size=(180, 50),
            halign='center'
        )

        self.bet_input.bind(on_text_validate=self.on_bet_entered)
        self.bet_input.bind(focus=self.on_bet_focus)

        left_panel.add_widget(balance_layout)
        left_panel.add_widget(bet_title)
        left_panel.add_widget(self.bet_input)
        left_panel.add_widget(stats_button)

        left_anchor.add_widget(left_panel)
        return left_anchor

    def on_bet_entered(self, instance):
        self._update_bet_from_input(instance.text)

    def on_bet_focus(self, instance, focused):
        if not focused:
            self._update_bet_from_input(instance.text)

    def _update_bet_from_input(self, text):
        try:
            new_bet = int(text)
            if 0 <= new_bet <= self.main_layout.saves["balance"]:
                self.main_layout.ui_bet = new_bet
            else:
                new_bet = self.main_layout.ui_bet
        except ValueError:
            new_bet = self.main_layout.ui_bet
        self.bet_input.text = str(new_bet)

    def toggle_settings(self, instance):
        self.right_panel_active = not self.right_panel_active
        if self.right_panel_active:
            self.toggle_box.clear_widgets()
            self.toggle_box.add_widget(self.tutorial_button)
            self.toggle_box.add_widget(self.volume_slider)
            self.toggle_box.add_widget(self.checkbox_layout1)
            self.toggle_box.add_widget(self.checkbox_layout2)
            self.toggle_box.add_widget(self.checkbox_layout3)
            self.toggle_box.add_widget(self.spinner)
        else:
            self.toggle_box.clear_widgets()

    def get_stats_tab(self):
        # Arka plan overlay
        stats_overlay = FloatLayout(size_hint=(1, 1))
        overlay_background = Button(
            size_hint=(1, 1),
            background_color=(0, 0, 0, 0.7),
            background_normal='',
        )
        overlay_background.bind(on_release=lambda x: self.stop_stats_tab_if_playing())
        stats_overlay.add_widget(overlay_background)

        stats_panel_background = Button(
            size_hint=(None, None),
            size=(1080, 1503),
            pos_hint={'center_x': 0.5, 'center_y': 0.5},
            background_normal='',
            background_color=(0.9, 0.95, 1, 1)
        )
        stats_overlay.add_widget(stats_panel_background)

        stats_panel = BoxLayout(
            orientation='vertical',
            size_hint=(None, None),
            size=(600, 1000),  # Daha geniş bir panel boyutu
            spacing=16,
            pos_hint={'center_x': 0.5, 'center_y': 0.5}
        )

        # Başlık
        title_label = Label(
            text=self.translator.get("playerstats"),
            font_size=40,
            color=(0, 0, 0, 1),
            size_hint=(None, None),
            size=(600, 75),
            halign='center',
            valign='middle',
            text_size=(600, 75)
        )
        # Label'in düzgün ortalanması için bind ekliyoruz
        title_label.bind(size=lambda instance, value: setattr(instance, 'text_size', value))
        stats_panel.add_widget(title_label)

        # Kayıtlı istatistikleri al
        stats = self.main_layout.saves
        stats_items = [
            (self.translator.get("balance"), stats["balance"]),
            (self.translator.get("wincount"), stats["win_count"]),
            (self.translator.get("losscount"), stats["loss_count"]),
            (self.translator.get("drawcount"), stats["draw_count"]),
            (self.translator.get("blackjackcount"), stats["blackjack_count"]),
            (self.translator.get("dealerblackjackcount"), stats["dealer_blackjack_count"]),
            (self.translator.get("fivecardcharliecount"), stats["five_card_charlie_count"]),
            (self.translator.get("bustcount"), stats["bust_count"]),
            (self.translator.get("totalbets"), stats["total_bets"]),
            (self.translator.get("totalearnings"), stats["total_earnings"]),
            (self.translator.get("largestwin"), stats["largest_win"]),
            (self.translator.get("hitcount"), stats["hit_count"]),
            (self.translator.get("standcount"), stats["stand_count"]),
            (self.translator.get("doublecount"), stats["double_count"]),
            (self.translator.get("surrendercount"), stats["surrender_count"]),
            (self.translator.get("languagepreference"), self.translator.current_language),
        ]

        # Her istatistik için label oluştur
        for stat_name, stat_value in stats_items:
            stat_text = f"{stat_name}: {stat_value}"
            stat_label = Label(
                text=stat_text,
                font_size=30,
                color=(0, 0, 0, 1),
                size_hint=(None, None),
                size=(600, 45),
                halign='center',
                valign='middle',
                text_size=(600, 45)  # halign/valign'in düzgün çalışması için
            )
            stat_label.bind(size=lambda instance, value: setattr(instance, 'text_size', value))
            stats_panel.add_widget(stat_label)

        # stats_panel'i overlay'e ekle
        stats_overlay.add_widget(stats_panel)
        self.stats_overlay = stats_overlay
        self.root.add_widget(stats_overlay)

    def stop_stats_tab_if_playing(self):
        if hasattr(self, 'stats_overlay') and self.stats_overlay:
            self.root.remove_widget(self.stats_overlay)
            self.stats_overlay.clear_widgets()

    def show_stats_tab(self):
        if not hasattr(self, 'stats_overlay') or not self.stats_overlay:
            self.get_stats_tab()
