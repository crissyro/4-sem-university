from kivy.app import App
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.properties import ObjectProperty, StringProperty
from kivy.core.window import Window
from kivy.uix.behaviors import ButtonBehavior
from kivy.uix.image import Image
import json
import os


COLOR_PRIMARY = (0.2, 0.6, 0.8, 1)
COLOR_SECONDARY = (0.9, 0.9, 0.9, 1)