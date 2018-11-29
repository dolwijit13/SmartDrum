"""
Credits go to: https://github.com/Zulko/pianoputer
"""

from scipy.io import wavfile
import numpy as np
import winsound
from flask import Flask, request

# Preprocess the keys and notes
app = Flask(__name__)

import pygame.mixer

up1 = pygame.mixer.Sound('tom3_heavy.ogg') 
left1 = pygame.mixer.Sound('kick_heavy.ogg')
right1 = pygame.mixer.Sound('crashr_studio.ogg')


@app.route("/")
def play():
    """
    index route, playing the note.

    accepts: /?key={key}

    e.g. /?key=10 to play note number 10
    """
    k = int(request.args.get('key'))
    if(k//100 == 0):
        left1.play(fade_ms=50)
    elif(k//100 == 1):
        up1.play(fade_ms=50)
    else:
        right1.play(fade_ms=50)
    return 'Playing key {}'.format(k)


# start the server at the port 5000
app.run(host = '0.0.0.0')
