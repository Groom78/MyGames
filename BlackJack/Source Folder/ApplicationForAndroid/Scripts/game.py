import random
import os
import sys

def get_base_path():
    if getattr(sys, 'frozen', False):
        return sys._MEIPASS
    return os.path.abspath(os.path.dirname(__file__))

class Card:
    def __init__(self, suit, rank, value):
        self.suit = suit
        self.rank = rank
        self.value = value

    def get_image_path(self, main_dir):
        suit_map = {
            "Hearts": "H",  # Kupa
            "Diamond": "D", # Karo
            "Club": "C",    # Sinek
            "Spade": "S"    # Maça
        }
        suit_str = suit_map[self.suit]
        rank_str = self.rank

        image_path = os.path.join(main_dir, "Assets", "Images", "Cards", "jpg", f"{suit_str}{rank_str}.jpg")
        return image_path

class Deck:
    suits = ["Hearts", "Diamond", "Club", "Spade"]
    ranks = {
       "A": 1,
       "2": 2,
       "3": 3,
       "4": 4,
       "5": 5,
       "6": 6,
       "7": 7,
       "8": 8,
       "9": 9,
       "10": 10,
       "J": 10,
       "Q": 10,
       "K": 10
    }

    def __init__(self, deck_count=1, shuffle_again=True):
        self.cards = []
        self.shuffle_again = shuffle_again
        self.deck_count = deck_count
        self.build_deck(deck_count)
        self.shuffle()

    def build_deck(self, deck_count):
        self.cards = []
        for _ in range(deck_count):
            for suit in self.suits:
                for rank, value in self.ranks.items():
                    self.cards.append(Card(suit, rank, value))

    def shuffle(self):
        random.shuffle(self.cards)

    def deal_card(self):
        if self.shuffle_again and len(self.cards) < self.deck_count * 52 * 75 / 100:
            self.build_deck(self.deck_count)
            self.shuffle()
        return self.cards.pop()


class Hand:
    def __init__(self, owner_name="Player"):
        self.owner_name = owner_name
        self.cards = []

    def add_card(self, card):
        if card:
            self.cards.append(card)
    
    def has_an_ace(self):
        for card in self.cards:
            if card.rank == "A":
                return True
        return False

    def calculate_score(self):
        total = 0
        aces = 0
        for card in self.cards:
            total += card.value
            if card.rank == "A":
                aces += 1
        
        while aces > 0:
            if total + 10 <= 21:
                total += 10
            aces -= 1

        return total

class Player:
    def __init__(self, name="Player"):
        self.name = name
        self.hand = Hand(owner_name=name)

class Dealer:
    def __init__(self, name="Dealer"):
        self.name = name
        self.hand = Hand(owner_name=name)

class Game:
    def __init__(self, deck_count=1):
        self.deck = Deck(deck_count=deck_count)
        self.player = Player(name="Player")
        self.dealer = Dealer(name="Dealer")
        self.is_over = False
        self.result = 0
