// SPDX-License-Identifier: GPL-3.0-or-later
// SDL2 queued PCM output. Matches working native SDL_AudioDevice API in PSJukebox.
#pragma once
#include "jungle_audio.hpp"
#include <SDL.h>
#include <array>
#include <cstdint>
#include <cstdio>

namespace snakex_audio {
class Output {
 Engine synth_;
 SDL_AudioDeviceID device_=0;
 bool subsystem_=false;
 public:
 bool open(){
  if(SDL_InitSubSystem(SDL_INIT_AUDIO)!=0)return false;
  subsystem_=true;
  SDL_AudioSpec want{};
  want.freq=kRate;want.format=AUDIO_S16SYS;want.channels=2;want.samples=1024;
  device_=SDL_OpenAudioDevice(nullptr,0,&want,nullptr,0);
  if(!device_){SDL_QuitSubSystem(SDL_INIT_AUDIO);subsystem_=false;return false;}
  SDL_PauseAudioDevice(device_,0);
  return true;
 }
 const char* error() const {return SDL_GetError();}
 void settings(bool music,bool effects,int volume,bool disco){
  synth_.set_settings(music,effects,volume,disco);
 }
 void play(Effect fx){synth_.trigger(fx);}
 void pump(){
  if(!device_)return;
  // Bound buffered latency and memory; audio never blocks the render loop.
  if(SDL_GetQueuedAudioSize(device_)>12288)return;
  std::array<int16_t,1024*2> pcm{};
  synth_.render(pcm.data(),1024);
  if(SDL_QueueAudio(device_,pcm.data(),uint32_t(pcm.size()*sizeof(int16_t)))!=0){
   SDL_CloseAudioDevice(device_);device_=0;
  }
 }
 void close(){
  if(device_){SDL_ClearQueuedAudio(device_);SDL_CloseAudioDevice(device_);device_=0;}
  if(subsystem_){SDL_QuitSubSystem(SDL_INIT_AUDIO);subsystem_=false;}
 }
 ~Output(){close();}
 bool ready() const {return device_!=0;}
};
} // namespace snakex_audio
