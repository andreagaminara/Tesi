#!/bin/bash

for site in www.facebook.com www.google.com www.youtube.com
do
    if [ "$site" = "www.google.com" ];
    then
	    for version in Q043 Q046 Q050 ID29 I001
	    do
		for i in {1..50}
		do
		    ./http_client -t -s $site -p / -v $version -K 
		done
	    done
    elif [ "$site" = "www.youtube.com" ];
    then
	    for version in Q043 Q046 Q050 ID29 I001
	    do
		for i in {1..50}
		do
		    ./http_client -t -s $site -p / -v $version -K 
		done
	    done
    else
	    for version in ID29 I001
	    do
		for i in {1..50}
		do
		    ./http_client -t -s $site -p / -v $version -K 
		done
	    done
    fi
done
