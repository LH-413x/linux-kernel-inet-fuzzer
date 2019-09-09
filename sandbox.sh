#!/bin/bash 

unshare -r -- unshare -n -- bash -c "$@"
