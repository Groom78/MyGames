import random
import os
import json
from kivy.clock import Clock
from kivy.core.window import Window
from kivy.uix.image import Image
from kivy.animation import Animation

class ChipRain:
    def __init__(self, chip_layer, main_dir):
        self.main_path = main_dir
        self.chip_layer = chip_layer
        self.chip_update_event = None
        self.falling_chips = []

    def start(self, type = "win"):
        if self.chip_update_event is None:
            self.chip_update_event = Clock.schedule_interval(lambda dt: self.update(dt, type=type), 1 / 60.0)

    def update(self, dt, type = "win"):
        for chip in self.falling_chips:
            chip.y -= 20

        if random.random() < 0.2:
            chip = Image(
                source=os.path.join(self.main_path, "Assets", "Images", "Others", "coin" + ("" if type == "win" else "bj") + ".png"),
                size_hint=(None, None),
                size=(80, 80),
                pos=(random.randint(0, int(Window.width - 32)), Window.height)
            )
            self.falling_chips.append(chip)
            self.chip_layer.add_widget(chip)

        for chip in self.falling_chips[:]:
            if chip.y < -32:
                self.falling_chips.remove(chip)
                self.chip_layer.remove_widget(chip)

    def stop(self):
        if self.chip_update_event:
            self.chip_update_event.cancel()
            self.chip_update_event = None
            for chip in self.falling_chips:
                self.chip_layer.remove_widget(chip)
            self.falling_chips.clear()

def try_percent(value):
    r = random.randint(1,100)
    return r <= value

def create_card_image(card=None, custom_path=None, main_path=None, card_scale=0.2):
        if custom_path:
            source = custom_path
        else:
            source = card.get_image_path(main_path)
        
        card_width_px = int(Window.width * card_scale)
        card_height_px = int(card_width_px * 1.4)
        
        return Image(
            source=source,
            size_hint=(None, None),
            size=(card_width_px, card_height_px),
            keep_ratio=True,
            allow_stretch=True
        )

def pulse_button_green(button):
        anim = (
            Animation(background_color=(0.0, 0.5, 0.0, 1), duration=0.5) +
            Animation(background_color=(0.0, 0.4, 0.0, 1), duration=0.5)
        )
        anim.repeat = True
        anim.start(button)

def pulse_button_yellow(button):
        anim = (
            Animation(background_color=(0.5, 0.5, 0.0, 1), duration=0.5) +
            Animation(background_color=(0.4, 0.4, 0.0, 1), duration=0.5)
        )
        anim.repeat = True
        anim.start(button)

def ensure_stats_file(base_dir):
    required_keys = {
        "balance": 1000,
        "wins": 0,
        "losses": 0,
        "draws": 0,
        "blackjack_count": 0,
        "language_preference": "English",
        "fivecardcharlie": True,
        "hitsonsoft17": False,
        "special_announcements": True,
        "bet_amount": 1,
        "hit_count": 0,
        "stand_count": 0,
        "double_count": 0,
        "surrender_count": 0,
        "bust_count": 0,
        "five_card_charlie_count": 0,
        "dealer_blackjack_count": 0,
        "total_earnings": 0,
        "largest_win": 0,
        "total_bets": 0,
    }

    stats_path = os.path.join(base_dir, "Saves", "save.json")

    if not os.path.exists(stats_path):
        os.makedirs(os.path.dirname(stats_path), exist_ok=True)
        with open(stats_path, "w") as f:
            json.dump({}, f, indent=4)

    with open(stats_path, "r") as f:
        try:
            data = json.load(f)
        except json.JSONDecodeError:
            data = {}

    updated = False
    for key, default_value in required_keys.items():
        if key not in data or not isinstance(data[key], dict) or "value" not in data[key]:
            data[key] = {"value": default_value}
            updated = True

    if updated:
        with open(stats_path, "w") as f:
            json.dump(data, f, indent=4)