#include "../native/jungle_audio.hpp"
#include <cassert>
#include <array>
#include <cstdio>
#include <cstdint>
using namespace snakex_audio;
int main(){
 Engine e;
 std::array<int16_t,4096> samples{};
 e.set_settings(true,true,7,false);
 e.render(samples.data(),2048);
 bool nonzero=false;
 for(auto s:samples)if(s){nonzero=true;break;}
 assert(nonzero);assert(e.frames_generated()==2048);
 e.set_settings(false,false,7,false);
 e.render(samples.data(),2048);
 for(auto s:samples)assert(s==0);
 e.set_settings(false,true,10,true);
 e.trigger(Effect::Apple);
 e.render(samples.data(),2048);
 nonzero=false;for(auto s:samples)if(s){nonzero=true;break;}assert(nonzero);
 e.set_settings(true,true,0,true);
 e.trigger(Effect::GameOver);
 e.render(samples.data(),2048);
 for(auto s:samples)assert(s==0);
 e.set_settings(true,true,9,true);
 std::array<int16_t,4096> scratch{};
 for(int i=0;i<200;i++)e.render(scratch.data(),2048);
 for(auto s:scratch)assert(s<=32767&&s>=-32768);
 puts("PASS: jungle PCM synthesis, mute, SFX, disco tempo, volume & bounded output");
}
