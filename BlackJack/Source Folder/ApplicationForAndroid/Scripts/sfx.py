import os
import random
from kivy.core.audio import SoundLoader
from kivy.clock import Clock

class SFX:
    def __init__(self, audio_path=None, play_welcome_sound=True):
        self.volume_level = 1.0
        self.welcome_delay = 0.4
        self.audio_path = audio_path
        welcome_sound = os.path.join(audio_path, "welcome.mp3")
        self.card_flip_sounds = [
            SoundLoader.load(os.path.join(audio_path, "card_flip1.mp3")),
            SoundLoader.load(os.path.join(audio_path, "card_flip2.mp3")),
            SoundLoader.load(os.path.join(audio_path, "card_flip3.mp3")),
            SoundLoader.load(os.path.join(audio_path, "card_flip4.mp3")),
        ]
        self.game_ending_sounds = [
            SoundLoader.load(os.path.join(audio_path, "win_music.mp3")),
            SoundLoader.load(os.path.join(audio_path, "draw_music.mp3")),
            SoundLoader.load(os.path.join(audio_path, "lose_music.mp3")),
        ]
        self.blackjack_announce_sounds = [
            SoundLoader.load(os.path.join(audio_path, f"bj{i}.mp3")) for i in range(1,11)
        ]
        self.shuffle_sounds = [
            SoundLoader.load(os.path.join(audio_path, "shuffle1.mp3")),
            SoundLoader.load(os.path.join(audio_path, "shuffle2.mp3")),
        ]
        self.blackjack_sounds = [
            SoundLoader.load(os.path.join(audio_path, "blackjack_sound.mp3"))
        ]
        self.funny_win_sounds = [
            SoundLoader.load(os.path.join(audio_path, f"win{i}.mp3")) for i in range(1,16)
        ]
        self.funny_lose_sounds = [
            SoundLoader.load(os.path.join(audio_path, f"lose{i}.mp3")) for i in range(1,16)
        ]
        self.funny_draw_sounds = [
            SoundLoader.load(os.path.join(audio_path, f"draw{i}.mp3")) for i in range(1,10)
        ]
        self.tutorial_sound = SoundLoader.load(os.path.join(audio_path, "tutorial.mp3"))
        self.tutorial_playing = False
        self.welcome_sound = SoundLoader.load(welcome_sound)
        if play_welcome_sound:
            Clock.schedule_once(lambda dt: self.welcome_sound.play(), self.welcome_delay)
    
    def stop_tutorial_ups_if_playing(self, *args):
        if self.tutorial_playing:
            self.tutorial_sound.stop()
            self.tutorial_playing = False

    def play_tutorial(self):
        if self.tutorial_sound:
            self.tutorial_sound.stop()
            self.tutorial_sound.play()
            self.tutorial_playing = True
    
    def play_flip_sound(self):
        sound = random.choice(self.card_flip_sounds)
        if sound:
            sound.play()
    def play_shuffle_sound(self):
        sound = random.choice(self.shuffle_sounds)
        if sound:
            sound.play()
    def play_blackjack_announce(self):
        sound = random.choice(self.blackjack_announce_sounds)
        if sound:
            sound.play()
    def play_blackjack_sound(self):
        sound = random.choice(self.blackjack_sounds)
        if sound:
            sound.play()

    def on_volume_change(self, instance, value):
        self.volume_level = value
        for s in self.card_flip_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.game_ending_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.shuffle_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.blackjack_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.funny_win_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.funny_lose_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.funny_draw_sounds:
            if s:
                s.volume = self.volume_level
        for s in self.blackjack_announce_sounds:
            if s:
                s.volume = self.volume_level
        if self.tutorial_sound:
            self.tutorial_sound.volume = self.volume_level
    
    def play_game_ending_sound(self, result):
        if result == "win":
            sound = self.game_ending_sounds[0]
        elif result == "draw":
            sound = self.game_ending_sounds[1]
        elif result == "lose":
            sound = self.game_ending_sounds[2]
        elif result == "blackjack_win":
            sound = self.play_blackjack_sound()
        elif result == "funny_win":
            sound = random.choice(self.funny_win_sounds)
        elif result == "funny_lose":
            sound = random.choice(self.funny_lose_sounds)
        elif result == "funny_draw":
            sound = random.choice(self.funny_draw_sounds)
        else:
            sound = None
        if sound is None:
            sound = SoundLoader.load(os.path.join(self.audio_path, "win_music.mp3"))
        if sound:
            sound.play()