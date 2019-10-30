#!/bin/sh
## prepare_results.sh for  in /Users/pouchet
## 
## Made by Louis-Noel Pouchet
## Contact: <pouchet@cs.ucla.edu>
## 
## Started on  Thu Jan 15 00:15:57 2015 Louis-Noel Pouchet
## Last update Thu Jan 15 01:46:42 2015 Louis-Noel Pouchet
##



function compute_metrics
{
    pred="$1";
    refdatabase="$2";
    type="$3";
    output_file="$4";
    countPred=0;
    countDb=0;
    ## Open files.
    exec 6< "$pred";
    exec 7< "$refdatabase";
    ## Skip first 5 lines of 'pred.csv'.
    count=0;
    while [ "$count" -lt 5 ]; do read foo <&6; count=$(($count+1)); done;
    ## Skip first 95 lines of 'pred.csv'.
    count=0;
    while [ "$count" -lt 95 ]; do read foo <&7; count=$(($count+1)); done;

    ## Scan the files.
    num_mispred=0;
    sumSlowdown=0;
    count=0;
    linePred=" ";
    ## 67 attributes before GF, att 7 at pos 86, so post74, so offset=-12
    offset="77";
    if [ "$type" = "cusp" ]; then offset=$(($offset+6)); fi;
    while ! [ -z "$linePred" ]; do
	read linePred <&6;
	read lineDB <&7;
	if [ -z "$linePred" ]; then break; fi;
	if [ -z "$lineDB" ]; then break; fi;
	## Get the predicted info.
    	inst=`echo "$linePred" | cut -d ' ' -f 1`;
    	correct=`echo "$linePred" | cut -d ' ' -f 2 | cut -d ':' -f 1`;
    	pred=`echo "$linePred" | cut -d ' ' -f 3 | cut -d ':' -f 1`;
    	#echo "inst=$inst correct=$correct pred=$pred";
	typePred=$(($pred+$offset));
	typeBest=$(($correct+$offset));
	## Get the DB value.
	gfPred=`echo "$lineDB" | cut -d ',' -f $typePred`;
	gfBest=`echo "$lineDB" | cut -d ',' -f $typeBest`;
	## Compute stats.
	if [ "$gfPred" != "0" ] && [ "$gfBest" != "0" ]; then
	    slowdown=`echo "scale=2; $gfBest/$gfPred" | bc`;
	else
	    slowdown=1;
	fi;
	#echo "gfpred=$gfPred gfbest=$gfBest diff=$slowdown";
	if [ "$typePred" != "$typeBest" ]; then mispred=$(($mispred+1)); fi;
	sumSlowdown=`echo "scale=2; $sumSlowdown+$slowdown" | bc`;
	count=$(($count+1));
	echo "$count $pred $correct $gfPred $gfBest $slowdown" >> $output_file;
    done;

    echo "mispredicted: $mispred/$count";
    avgSlow=`echo "scale=2; $sumSlowdown/$count" | bc`;
    echo "avg. slowdown: $avgSlow";
    
    ## Close files.
    6<&-;
    7<&-;
}

compute_metrics "$1" "$2" "cusp" "results.csv";

