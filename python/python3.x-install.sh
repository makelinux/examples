#!/bin/sh

grep --quiet deadsnakes/ppa --recursive /etc/apt/sources.list.d/ || sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get update

for v in {0..10}; do
	which python3.$v || sudo apt-get --yes install python3.$v
done

