#!/bin/sh

SESSIO=oratio
MANDATUM=destinatum/rosario

if [ ! -f $MANDATUM ]; then
	echo Cave! Mandatum "$MANDATUM" non est! Facere conantur...
	make $MANDATUM
	if [ ! -f $MANDATUM ]; then
		echo Remitto!
		exit 1
	else
		echo Opus superabat! Mandato fungor...
	fi
fi

if [ -z $1 ]; then
	exec screen -dmS $SESSIO $0 fungi
else
	while true; do
		exec $MANDATUM
	done
fi

exit 0
