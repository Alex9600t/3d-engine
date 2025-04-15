#include "audio.h"

float Audio::volume = 100;

void Audio::play(std::string name) {
    sf::Music music;
    if (!music.openFromFile("game/resources/music/" + name + ".wav")){}

    music.setLooping(true);
    music.setVolume(volume);
    music.play();

    while (music.getStatus() == sf::SoundSource::Status::Playing) {
        music.setVolume(volume);
    }
}