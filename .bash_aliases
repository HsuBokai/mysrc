#! bin/bash

function G++(){
	#g++ -g -Wall -o $@ $@.cpp;
	CFLAGS="$CFLAGS" make $@;
}

alias vi=vim
alias rm='rm -i'
alias laf='ls -al |grep '^-' |more'
alias lad='ls -al |grep '^d' |more'
alias vimtemp='vim /home/bokai/mysrc/temp.cpp'
alias gtemp='sh -c "cd ~/mysrc; make;"'
alias sshalg='ssh -p 40064 alg_053@edaunion.ee.ntu.edu.tw'

alias ns2='~/mysrc/ns-allinone-2.35/bin/ns'
#alias ns3='~/mysrc/ns-2.33-pmext-1.0/ns'

