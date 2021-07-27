#!/bin/bash

export GIT_PS1="($(git branch | cut -c 3-))"
export PS1='\[\033]0;$TITLEPREFIX:$PWD\007\]\n\[\033[32m\]\u@PC \[\033[33m\]${PWD##*/}\[\033[36m\] ${GIT_PS1}\[\033[0m\]\n$ '

## Helper Functions/Commands

md () { [ $# = 1 ] && mkdir -p "$@" && cd "$@" || echo "Error - no directory passed!"; }
