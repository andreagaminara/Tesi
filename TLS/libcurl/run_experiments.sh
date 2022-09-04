#!/bin/bash

for site in www.google.com www.youtube.com www.facebook.com
do
    for version in TLS_1_2 TLS_1_3
    do
        for i in {1..50}
        do
            if [ $version = 'TLS_1_2' ]
            then
                ./tls_perf -4 -2 -u $site -p 443 
                #>> output/${site}_${version}_results.txt
            else
                ./tls_perf -4 -3 -2 -u $site -p 443 
                #>> output/${site}_${version}_results.txt
            fi
        done
    done
done
