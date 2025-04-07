import os
import json
from kivy.storage.jsonstore import JsonStore

class Translator:
    def __init__(self, main_dir = None, initial="English"):
        self.current_language = initial
        self.main_path = main_dir
        self.items = dict()
        self.store = JsonStore(os.path.join(self.main_path, "Saves", "save.json"))
        translations_path = os.path.join(main_dir, "Scripts", "languages.json")
        with open(translations_path, "r", encoding="utf-8") as f:
            self.translations = json.load(f)
        
        self.choices = (
            'Bengali',
            'Chinese',
            'English',
            'French',
            'German',
            'Hindi',
            'Italian',
            'Japanese',
            'Korean',
            'Portuguese',
            'Russian',
            'Spanish',
            'Turkish',
            'Urdu',
            'Vietnamese'
        )

    def on_language_change(self, spinner, text):
        self.current_language = text
        self.store.put("language_preference", value=self.current_language)
        if "fivecardcharlie" in self.items:
            self.items["fivecardcharlie"].text = self.get("fivecardcharlie")
        if "hitsonsoft17" in self.items:
            self.items["hitsonsoft17"].text = self.get("hitsonsoft17")
        if "betamount" in self.items:
            self.items["betamount"].text = self.get("betamount")
        if "hit_button" in self.items:
            self.items["hit_button"].text = self.get("hit")
        if "stand_button" in self.items:
            self.items["stand_button"].text = self.get("stand")
        if "double_button" in self.items:
            self.items["double_button"].text = self.get("2x")
        if "surrender_button" in self.items:
            self.items["surrender_button"].text = self.get("surrender")
        if "wins" in self.items:
            self.items["wins"].text = self.get("win")
        if "losses" in self.items:
            self.items["losses"].text = self.get("lose")
        if "draws" in self.items:
            self.items["draws"].text = self.get("draw")
        if "restart_button" in self.items:
            self.items["restart_button"].text = self.get("rematch")
        if "hit_button2" in self.items:
            self.items["hit_button2"].text = self.get("hit")
        if "stand_button2" in self.items:
            self.items["stand_button2"].text = self.get("stand")
        if "specialannounces" in self.items:
            self.items["specialannounces"].text = self.get("specialannounces")
        
    def get(self, key):
        language = self.current_language
        lang = language.lower()
        if key in self.translations and lang in self.translations[key]:
            return self.translations[key][lang]
        else:
            print(f"[{key} - {lang} not found] {self.current_language}")
            return f"[{key} - {lang} not found]"