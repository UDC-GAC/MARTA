#!/bin/sh
## run_all_exps.sh for  in /Users/pouchet
## 
## Made by Louis-Noel Pouchet
## Contact: <pouchet@cs.ucla.edu>
## 
## Started on  Wed Jan 14 15:13:32 2015 Louis-Noel Pouchet
## Last update Sat Jan 17 06:50:28 2015 Louis-Noel Pouchet
##

## Global variable to be edited.
WEKA_ABS_JAR_PATH=/Users/pouchet/projects/Weka/weka-3-6-12/weka.jar

######################################################################

## Contain all the arff files for experiments.
DIR_PATH_TO_ARFF_FILES=data/ARFF;
DIR_PATH_RESULTS=results;
ALL_RESULTS_FILENAME=all_results_k40_trial.csv;
## In this directory, files must be exactly named as follows:
## {cusp,cusparse}_{base,extended1}_{rand1..5,all}_{train,test}.arff
## that is there is one .arff file for the Cartesian product of all
## these possibilities. 

# if [ $# -ne 7 ];  then
#     echo "usage: <algo> <model_file> <test_file> <output_predictions_file> <reference_arff> <somefilename>"
#     exit 1;
# fi;


function compute_metrics
{
    pred="$1";
    refdatabase="$2";
    type="$3";
    output_file="$4";
    output_stats_file="$5";
    output_stat_prefix="$6";
    countPred=0;
    countDb=0;
    ## Open files.
    if ! [ -f "$pred" ]; then
	echo "ERROR: prediction file $pred does not exist"; exit 1;
    fi;
    if ! [ -f "$refdatabase" ]; then
	echo "ERROR: full database file $refdatabase does not exist"; exit 1;
    fi;
    echo "Compute stats on $pred and $refdatabase";
    exec 6< "$pred";
    exec 7< "$refdatabase";
    ## Skip first 5 lines of 'pred.csv'.
    count=0;
    while [ "$count" -lt 5 ] || [ -z "$foo" ]; do read foo <&6; count=$(($count+1)); done;
    ## Skip first 95 lines of 'pred.csv'.
    count=0;
    while [ "$count" -lt 95 ] || [ -z "$foo" ]; do read foo <&7; count=$(($count+1)); done;

    ## Scan the files.
    mispred=0;
    sumSlowdown=0;
    maxSlow=100000;
    slowAboveThresCount=0;
    slowThresold=0.75;
    slowAboveThresCount2=0;
    slowThresold2=0.5;
    count=0;
    linePred=" ";
    ## 67 attributes before GF, att 7 at pos 86, so post74, so offset=-12
    offset="77";
    if [ "$type" = "cusp" ]; then offset=$(($offset+6)); fi;
    while ! [ -z "$linePred" ]; do
	read linePred <&6;
	read lineDB <&7;
	if [ -z "$linePred" ]; then break; fi;
	## Skip initial whiteline after @data, if any.
	while [ -z "$lineDB" ]; do read lineDB <&7; done;
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
	    slowdown=`echo "scale=2; $gfPred/$gfBest" | bc`;
	else
	    slowdown=0;
	fi;
	#echo "gfpred=$gfPred gfbest=$gfBest diff=$slowdown";
	if [ "$typePred" != "$typeBest" ]; then mispred=$(($mispred+1)); fi;
	sumSlowdown=`echo "scale=2; $sumSlowdown+$slowdown" | bc`;
	count=$(($count+1));
	isMax=`echo "$maxSlow < $slowdown" | bc`;
	isAboveThres=`echo "$slowThresold <= $slowdown" | bc`;
	isAboveThres2=`echo "$slowThresold2 <= $slowdown" | bc`;
	if [ "$isMax" = "0" ]; then maxSlow=$slowdown; fi;
	if [ "$isAboveThres" = "0" ]; then slowAboveThresCount=$(($slowAboveThresCount+1)); fi;
	if [ "$isAboveThres2" = "0" ]; then slowAboveThresCount2=$(($slowAboveThresCount2+1)); fi;
	echo "$count $pred $correct $gfPred $gfBest $slowdown" >> $output_file;
    done;

    #echo "mispredicted: $mispred/$count";
    avgSlow=`echo "scale=2; $count/$sumSlowdown" | bc`;
    mispredRatio=`echo "scale=2; $mispred/$count" | bc`;
    echo "avg. slowdown: $avgSlow";
    echo "$output_stat_prefix $mispred $count $mispredRatio $maxSlow $slowAboveThresCount $slowAboveThresCount2 $avgSlow" >> $output_stats_file;
    ## Close files.
    6<&-;
    7<&-;
}


rootdir=`pwd`;
#rm -f $ALL_RESULTS_FILENAME;
for expe in trial; do
    for featSet in base; do
	for Algo in BFTree; do
	    for minObj in 2; do
		for maxLeaf in 5; do
		    for i in `seq 1 5` all; do
			if [ "$i" != "all" ]; then i="rand$i"; fi;
			usc="_"; train="train"; test="test";
			basefile=$expe$usc$featSet$usc$i;
			foldername="expe_$basefile$usc$Algo$usc$minObj$usc$maxLeaf";
			echo "Running experiment $foldername";
			mkdir -p $DIR_PATH_RESULTS/$foldername;
			cd $DIR_PATH_RESULTS/$foldername;
			trainfile=$rootdir/$DIR_PATH_TO_ARFF_FILES/$basefile$usc$train;
			testfile=$rootdir/$DIR_PATH_TO_ARFF_FILES/$basefile$usc$test;
			# if ! [ -f "$trainfile.arff" ]; then
			#     echo "ERROR: file ./$trainfile.arff not found for experiment $foldername";
			#     cd $rootdir;
			#     continue;
			# fi;
			# if ! [ -f "$testfile.arff" ]; then
			#     echo "ERROR: file $testfile.arff not found for experiment $foldername";
			#     cd $rootdir;
			#     continue;
			# fi;
			echo "Produce classified outputs...";
			java -cp $WEKA_ABS_JAR_PATH weka.classifiers.trees.BFTree -l $1 -T $2 -p 0 > "gfs_stats_$foldername.csv";

			## Prepare results.
			rm -f "train_stats_summary_gfs_$foldername.csv";
			rm -f "gfs_stats_$foldername.csv";
			compute_metrics "pred_$foldername.csv" "$4" "$expe" "gfs_stats_$foldername.csv" "$rootdir/$ALL_RESULTS_FILENAME" "";
			cd $rootdir;
		    done;
		done;
	    done;
	done;
    done;
done;		


			# java -cp $WEKA_ABS_JAR_PATH weka.classifiers.trees.$1 -l $2 -T $3 -p 0 > $4;

			# ## Prepare results.
			# rm -f "train_stats_summary_gfs_$foldername.csv";
			# rm -f "gfs_stats_$foldername.csv";
			# compute_metrics "$4" "$5" "oneexp" "$6" "$7" "";
