#!/bin/sh

echo '!RGllIGVpbnppZ2VuIFNvbmRlc??nplaWNoZW4gaW0gQmFzZTY0IEFscGhhYmV0IHNpbmQg_Iisg_L_y_A9Ii4gQWxsZSB3ZWl0ZXJlbi-B-T-b25kZXJ6!ZWljaGVuICIhIsKnJCUiIGtvbW1_!lbiBkb3J0IG5pY2h0IHZvci"4=' | awk '{ gsub(/[^A-Za-z0-9\/\+\=]/, ""); print $0 }' | base64 --decode
