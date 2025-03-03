#!/bin/bash

arduino-cli compile -b esp32:esp32:esp32 . -v --board-options DebugLevel=debug --board-options PartitionScheme=huge_app