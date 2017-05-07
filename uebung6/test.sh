#!/bin/sh

SERVER="$1"
CLIENT="$2"

./"$SERVER" cities.txt &
PID=$!

echo "Server running (PID $PID)."

sleep 3

./"$CLIENT" 127.0.0.1 5000 innsbruck bregenzinnsbruck bregenz

echo "Killing server."
kill $PID
