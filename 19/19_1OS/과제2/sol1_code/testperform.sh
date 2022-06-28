#!/bin/bash
timeout 5s ./testEnqueue 2 &
timeout 5s ./testEnqueue 3 &
timeout 5s ./testEnqueue 4 &
timeout 5s ./testDequeue &
timeout 5s ./testDequeue &
timeout 5s ./testDequeue &

timeout 5s ./testRead &
timeout 5s ./testRead &
timeout 5s ./testRead &
timeout 5s ./testRead &
timeout 5s ./testRead &
timeout 5s ./testRead &






