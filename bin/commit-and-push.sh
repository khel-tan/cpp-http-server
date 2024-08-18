#!/bin/bash

if [[ "$#" -eq "1" ]]; then
  git_command="git add . && git commit -m '$1' && git push"
  echo "Executing ---> $git_command"
  eval "$git_command"
else
  echo "Please specify a commit message"
fi
