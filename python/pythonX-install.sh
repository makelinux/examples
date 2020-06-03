#!/bin/sh

grep --quiet deadsnakes/ppa --recursive /etc/apt/sources.list.d/ || sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get -q update

for v in 2.{3..7} 3.{1..9}; do
	which python$v || sudo apt-get --yes install python$v
done

