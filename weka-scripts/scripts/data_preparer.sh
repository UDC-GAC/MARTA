#!/bin/sh
## data_preparer.sh for  in /Users/pouchet
##
## Made by Louis-Noel Pouchet
## Contact: <pouchet@cs.ucla.edu>
##
## Started on  Wed Jan 14 22:47:58 2015 Louis-Noel Pouchet
## Last update Sat Jan 17 05:24:31 2015 Louis-Noel Pouchet
##

## Global variables to be edited.
WEKA_ABS_JAR_PATH=/Users/pouchet/projects/Weka/weka-3-6-12/weka.jar
FORCE_REPLACE_FILES=yes;
ARFF_ALL_DATA_FILE=alldata_k20c.sp.arff


#########################################
ABS_PROJECT_DIR=.
ABS_ARFF_DATA_PREFIX=$ABS_PROJECT_DIR/data/ARFF


## Format:
## {cusp,cusparse}_{base,extended1}_{rand1..5,all}_{train,test}.arff

function create_dataset
{
  libtype="$1";
  dataset_name="$2";
  feature_list="$3";
  suffix="_all_train.arff";
  usc="_";
  outfilename=$libtype$usc$dataset_name$suffix;

  ## create the "all" dataset (testing and training are identical).
  if ! [ -f "$ABS_ARFF_DATA_PREFIX/$outfilename" ] || [ "$FORCE_REPLACE_FILES" != "no" ]; then
    s=`sed -e 's/@attribute best.cusp.rep.*/@attribute best.cusp.rep {cusp.gflops.cu-coo,cusp.gflops.cu-ell,cusp.gflops.cu-csr,cusp.gflops.cu-hyb,cusp.gflops.cu-dia}/1' $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE > __tmp`;
    s=`mv __tmp $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE`;
    echo "Generate file $outfilename...";
    $ABS_PROJECT_DIR/scripts/subset_data.sh "$feature_list" $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE > $ABS_ARFF_DATA_PREFIX/$outfilename;
    s=`sed -e 's/@attribute best.cusp.rep.*/@attribute best.cusp.rep {cusp.gflops.cu-coo,cusp.gflops.cu-ell,cusp.gflops.cu-csr,cusp.gflops.cu-hyb,cusp.gflops.cu-dia}/1' $ABS_ARFF_DATA_PREFIX/$outfilename > __tmp`;
    s=`mv __tmp $ABS_ARFF_DATA_PREFIX/$outfilename`;
    ## create $libtype_full_all_train.arff, the full db.
    fl="full"
    cp $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE $ABS_ARFF_DATA_PREFIX/$libtype$usc$fl$suffix;
  fi;
  
  suffix="_all_test.arff";
  outfilename2=$libtype$usc$dataset_name$suffix;
  if ! [ -f "$ABS_ARFF_DATA_PREFIX/$outfilename2" ] || [ "$FORCE_REPLACE_FILES" != "no" ]; then
	  echo "Generate file $outfilename2...";
	  cp $ABS_ARFF_DATA_PREFIX/$outfilename $ABS_ARFF_DATA_PREFIX/$outfilename2;
	  ## create $libtype_full_all_test.arff, the full db.
	  fl="full"
	  cp $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE $ABS_ARFF_DATA_PREFIX/$libtype$usc$fl$suffix;
  fi;
  for i in `seq 1 5`; do
    pref="_full_rand";
    rd="rand";
    prefout=$libtype$usc$dataset_name$usc$rd;
    suff="_train.arff";
    inputfilename="$ABS_ARFF_DATA_PREFIX/$libtype$pref$i$suff";
	  if ! [ -f "$ABS_ARFF_DATA_PREFIX/$prefout$i$suff" ] || [ "$FORCE_REPLACE_FILES" != "no" ]; then
      echo "Generate file $ABS_ARFF_DATA_PREFIX/$prefout$i$suff...";
    	$ABS_PROJECT_DIR/scripts/subset_data.sh "$feature_list" $inputfilename > $ABS_ARFF_DATA_PREFIX/$prefout$i$suff;
	    s=`sed -e 's/@attribute best.cusp.rep.*/@attribute best.cusp.rep {cusp.gflops.cu-coo,cusp.gflops.cu-ell,cusp.gflops.cu-csr,cusp.gflops.cu-hyb,cusp.gflops.cu-dia}/1' $ABS_ARFF_DATA_PREFIX/$prefout$i$suff > __tmp`;
	    s=`mv __tmp $ABS_ARFF_DATA_PREFIX/$prefout$i$suff`;
	    fi;
    	suff="_test.arff";
    	inputfilename="$ABS_ARFF_DATA_PREFIX/$libtype$pref$i$suff";
	    if ! [ -f "$ABS_ARFF_DATA_PREFIX/$prefout$i$suff" ] || [ "$FORCE_REPLACE_FILES" != "no" ]; then
    	    echo "Generate file $ABS_ARFF_DATA_PREFIX/$prefout$i$suff...";
    	    $ABS_PROJECT_DIR/scripts/subset_data.sh "$feature_list" $inputfilename > $ABS_ARFF_DATA_PREFIX/$prefout$i$suff;

	    s=`sed -e 's/@attribute best.cusp.rep.*/@attribute best.cusp.rep {cusp.gflops.cu-coo,cusp.gflops.cu-ell,cusp.gflops.cu-csr,cusp.gflops.cu-hyb,cusp.gflops.cu-dia}/1' $ABS_ARFF_DATA_PREFIX/$prefout$i$suff > __tmp`;
	    s=`mv __tmp $ABS_ARFF_DATA_PREFIX/$prefout$i$suff`;
	    fi;
  done;
}


## 0. Create the 80-20 files, on the full ARFF files, if they do not exist.
for type in cusp cusparse; do
    for i in `seq 1 5`; do
	## training.
	pref="_full_rand";
	suff="_train.arff";
	if ! [ -f "$ABS_ARFF_DATA_PREFIX/$type$pref$i$suff" ] || [ "$FORCE_REPLACE_FILES" != "no" ]; then
	    echo "Generate file $ABS_ARFF_DATA_PREFIX/$type$pref$i$suff";
	    java -cp $WEKA_ABS_JAR_PATH weka.filters.supervised.instance.StratifiedRemoveFolds  -i $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE -c last -o $ABS_ARFF_DATA_PREFIX/$type$pref$i$suff -N 5 -F $i -V -S 42;
	fi;
	## testing.
	suff="_test.arff";
	if ! [ -f "$ABS_ARFF_DATA_PREFIX/$type$pref$i$suff" ] || [ "$FORCE_REPLACE_FILES" != "no" ]; then
	    echo "Generate file $ABS_ARFF_DATA_PREFIX/$type$pref$i$suff";
	    java -cp $WEKA_ABS_JAR_PATH weka.filters.supervised.instance.StratifiedRemoveFolds  -i $ABS_ARFF_DATA_PREFIX/$ARFF_ALL_DATA_FILE -c last -o $ABS_ARFF_DATA_PREFIX/$type$pref$i$suff -N 5 -F $i -S 42;
	fi;
    done;
done;

## 1. Prepare set of features "base"
create_dataset "cusparse" "base" "nnz_frac nnz_mu nnz_sigma best.cusparse.rep";
create_dataset "cusp" "base" "nnz_frac nnz_mu nnz_sigma best.cusp.rep";

## 2. Prepare set of features "extended1"
create_dataset "cusparse" "extended1" "nnz_frac nnz_mu nnz_sigma nnzb_mu nnzb_sigma snzb_mu snzb_sigma best.cusparse.rep";
create_dataset "cusp" "extended1" "nnz_frac nnz_mu nnz_sigma nnzb_mu nnzb_sigma snzb_mu snzb_sigma best.cusp.rep";

## 3. Prepare set of features "extended2"
create_dataset "cusparse" "extended2" "nnz_frac nnz_max nnz_mu nnz_sigma nnzb_mu nnzb_sigma snzb_mu snzb_sigma best.cusparse.rep";
create_dataset "cusp" "extended2" "nnz_frac nnz_max nnz_mu nnz_sigma nnzb_mu nnzb_sigma snzb_mu snzb_sigma best.cusp.rep";

echo "=> Data prepared, all done.";
