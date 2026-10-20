// SPDX-License-Identifier: GPL-3.0-or-later
// SnakeX original synthesised 16-bit jungle score by YAHBALLON.
// No external music samples or decoder. Portable, deterministic PCM synthesis.
#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <cstddef>

namespace snakex_audio {
constexpr int kRate=48000;
constexpr float kTau=6.28318530718f;
enum class Effect : uint8_t { Menu, Start, Apple, Pause, GameOver };
inline float frac(float x){return x-std::floor(x);}
inline float sine(float cycles){return std::sin(kTau*cycles);}
inline float triangle(float cycles){return 4.f*std::fabs(frac(cycles)-.5f)-1.f;}
inline float note(int semitone){return 440.f*std::pow(2.f,(float(semitone)-69.f)/12.f);}
struct Voice {
 Effect kind=Effect::Menu;
 uint64_t start=0;
 float duration=0;
 bool active=false;
};
class Engine {
 uint64_t frame_=0;
 uint32_t noise_=0x55abb119;
 float filtered_=0.f, filtered2_=0.f;
 std::array<Voice,6> voices_{};
 bool music_=true, effects_=true, disco_=false;
 int volume_=7;
 float random(){
  noise_^=noise_<<13;noise_^=noise_>>17;noise_^=noise_<<5;
  return float(noise_&0xffffu)*(2.f/65535.f)-1.f;
 }
 static float clip(float a){return std::clamp(a,-.96f,.96f);}
 float synth_music(float t,float n){
  constexpr int melody[16]={76,-1,79,83,81,-1,79,76,74,76,-1,79,72,74,76,-1};
  constexpr int bass[4]={40,43,45,38};
  const float tempo=disco_?1.91f:1.72f;
  const float beat=t*tempo;
  const float eighth=beat*2.f;
  const int idx=int(std::floor(eighth))%16;
  const float step=frac(eighth);
  const float lead=melody[idx]<0?0.f:
   (.62f*triangle(t*note(melody[idx]))+.38f*sine(t*note(melody[idx])*2.f))
   *std::pow(1.f-step,1.75f)*.15f;
  const float bassHz=note(bass[int(beat/4.f)%4]);
  const float bassTone=(.75f*triangle(t*bassHz)+.25f*sine(t*bassHz))* .105f;
  // Lo-fi percussion: hollow jungle toms, two syncopated rattles and kick.
  const float pulse=frac(beat);
  const float kick=std::exp(-pulse*17.f)*sine(t*(58.f+120.f*std::exp(-pulse*26.f)))*.18f;
  const float tomPulse=frac(beat+.5f);
  const float tom=std::exp(-tomPulse*19.f)*sine(t*(175.f-75.f*tomPulse))*.075f;
  const float hat=std::exp(-frac(beat*4.f)*44.f)*n*.055f;
  // Layered rainforest: wind, chirping birds, cicadas, digital rain.
  filtered_+=.0025f*(n-filtered_);
  filtered2_+=.018f*(n-filtered2_);
  const float wind=filtered_*.17f+filtered2_*.022f;
  const float birdPhase=frac(t/3.7f);
  const float birdEnv=birdPhase<.18f?std::sin(birdPhase/.18f*3.14159265f)*.085f:0.f;
  const float birds=birdEnv*sine(t*(1170.f+410.f*birdPhase)+1.7f*sine(t*8.f));
  const float cricket=(.008f+.007f*sine(t*.13f))*sine(t*1940.f)*sine(t*4.5f);
  return lead+bassTone+kick+tom+hat+wind+birds+cricket;
 }
 float sound_fx(float t){
  float out=0;
  for(auto& voice:voices_){
   if(!voice.active)continue;
   const float age=float(frame_-voice.start)/float(kRate);
   if(age>=voice.duration){voice.active=false;continue;}
   const float u=age/voice.duration;
   const float fade=(1.f-u)*(1.f-u);
   switch(voice.kind){
   case Effect::Menu: out+=sine(t*(630.f+180.f*u))*.16f*fade;break;
   case Effect::Start: out+=triangle(t*(390.f+520.f*u))*.23f*fade;break;
   case Effect::Apple:
    out+=(sine(t*(620.f+880.f*u))*.68f+triangle(t*(930.f+350.f*u))*.32f)*.31f*fade;break;
   case Effect::Pause: out+=triangle(t*(515.f-110.f*u))*.17f*fade;break;
   case Effect::GameOver:
    out+=(triangle(t*(400.f-335.f*u))*.7f+sine(t*(275.f-190.f*u))*.3f)*.30f*fade;
    break;
   }
  }
  return out;
 }
 public:
 void set_settings(bool music,bool effects,int volume,bool disco){
  music_=music;effects_=effects;volume_=std::clamp(volume,0,10);disco_=disco;
 }
 void trigger(Effect fx){
  if(!effects_)return;
  Voice* freeVoice=nullptr;
  for(auto& v:voices_)if(!v.active){freeVoice=&v;break;}
  if(!freeVoice)freeVoice=&voices_[0];
  const float length=fx==Effect::GameOver?.68f:fx==Effect::Apple?.21f:fx==Effect::Start?.27f:.11f;
  *freeVoice={fx,frame_,length,true};
 }
 void render(int16_t* out,size_t frames){
  if(!out)return;
  const float gain=volume_*.077f;
  for(size_t i=0;i<frames;i++,frame_++){
   const float t=float(frame_%(uint64_t(kRate)*600))/float(kRate);
   const float n=random();
   const float bg=music_?synth_music(t,n):0.f;
   const float fx=effects_?sound_fx(t):0.f;
   const float combined=clip((bg+fx)*gain);
   const int16_t sample=int16_t(combined*32767.f);
   out[2*i]=sample;out[2*i+1]=sample;
  }
 }
 uint64_t frames_generated() const {return frame_;}
};
} // namespace snakex_audio
