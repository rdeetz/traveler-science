#!/bin/bash

clang `pkg-config --cflags --libs libpq` ./traveler.c -o ./bin/traveler
