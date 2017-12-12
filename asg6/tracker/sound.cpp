#include <string>
#include <iostream>
#include <ctime>
#include "sound.h"
using std::string;

SDLSound::~SDLSound() {
  std::cout << "Cleaning up sounds ..." << std::endl;
  std::clock_t start = std::clock();
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  for (unsigned int i = 0; i < sounds.size(); ++i) {
    Mix_FreeChunk(sounds[i]);
  }
  Mix_CloseAudio();
  std::clock_t duration = std::clock() - start;
  std::cout << "Clean up took " << duration << " ticks\n";
}

SDLSound::SDLSound() :
  volume(SDL_MIX_MAXVOLUME/4),
  currentSound(-1),
  music(NULL),
  victory(NULL),
  audioRate(22050),
  audioChannels(2),
  audioBuffers(4096),
  sounds(),
  channels()
{

  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels,
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  music = Mix_LoadMUS(Gamedata::getInstance().getXmlStr("audio/music").c_str());
  victory = Mix_LoadMUS(Gamedata::getInstance().getXmlStr("audio/victory").c_str());
  // Need to install midi to play the following:
  // music = Mix_LoadMUS("sound/ballad2.mid");
  if (!music) throw string("Couldn't load game music. ")+Mix_GetError();
  if (!victory) throw string("Couldn't load game music. ")+Mix_GetError();

  startMusic();

  // get audio files loaded in
  sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr("audio/bark").c_str()) ); // Dog barking sound
  sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr("audio/bump").c_str()) ); // Player/terrain collision
  //sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr("audio/chew")) ); // Dog when contact with treat
  sounds.push_back( Mix_LoadWAV(Gamedata::getInstance().getXmlStr("audio/door").c_str()) ); // Door closes when dog returned
  for (unsigned int i = 0; i < sounds.size(); ++i) channels.push_back(i);
  std::cout << "Music and Sound is loaded" << std::endl;
}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) {
    Mix_ResumeMusic();
  }
  else {
    Mix_PauseMusic();
  }
}

void SDLSound::setSound(int index){
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume * 2.5);
  channels[index] =
     Mix_PlayChannel(-1, sounds[index], 0);
}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

void SDLSound::playVictoryMusic() {
  stopMusic();
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(victory, -1);  
}
