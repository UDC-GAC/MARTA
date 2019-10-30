#!/bin/sh
## subset_data.sh for  in /Users/pouchet
##
## Made by Louis-Noel Pouchet
## Contact: <pouchet@cs.ucla.edu>
##
## Started on  Wed Jan 14 22:39:04 2015 Louis-Noel Pouchet
## Last update Fri Jan 16 21:26:14 2015 Louis-Noel Pouchet
##

## Global variable to be edited.
WEKA_ABS_JAR_PATH=/Users/pouchet/projects/Weka/weka-3-6-12/weka.jar


###################################################################

if [ $# -ne 2 ]; then
    echo "ERROR: missing argument";
    echo "Usage: ./subset_data.sh \"column_name1 column_name2 ...\" inputfile.arff";
    echo "       where column_name1 etc. are name of columns to appear in the";
    echo "       output dataset.";
    echo "";
    echo "Column names: ";
    echo "matrix group n_rows n_cols nnz_tot nnz_frac nnz_min nnz_max nnz_mu nnz_sigma nnzb_tot nnzb_min nnzb_max nnzb_mu nnzb_sigma snzb_min snzb_max snzb_mu snzb_sigma coord type cusparse.coo.conv_ok cusparse.coo.t_h2d cusparse.coo.t_conv cusparse.coo.t_kernel cusparse.coo.t_d2h cusparse.ell.conv_ok cusparse.ell.t_h2d cusparse.ell.t_conv cusparse.ell.t_kernel cusparse.ell.t_d2h cusparse.csr.conv_ok cusparse.csr.t_h2d cusparse.csr.t_conv cusparse.csr.t_kernel cusparse.csr.t_d2h cusparse.hyb.conv_ok cusparse.hyb.t_h2d cusparse.hyb.t_conv cusparse.hyb.t_kernel cusparse.hyb.t_d2h cusparse.hyb_mu.conv_ok cusparse.hyb_mu.t_h2d cusparse.hyb_mu.t_conv cusparse.hyb_mu.t_kernel cusparse.hyb_mu.t_d2h cusparse.bsr.conv_ok cusparse.bsr.t_h2d cusparse.bsr.t_conv cusparse.bsr.t_kernel cusparse.bsr.t_d2h cusp.coo.conv_ok cusp.coo.t_h2d cusp.coo.t_conv cusp.coo.t_kernel cusp.coo.t_d2h cusp.ell.conv_ok cusp.ell.t_h2d cusp.ell.t_conv cusp.ell.t_kernel cusp.ell.t_d2h cusp.csr.conv_ok cusp.csr.t_h2d cusp.csr.t_conv cusp.csr.t_kernel cusp.csr.t_d2h cusp.hyb.conv_ok cusp.hyb.t_h2d cusp.hyb.t_conv cusp.hyb.t_kernel cusp.hyb.t_d2h cusp.hyb.ellw cusp.dia.conv_ok cusp.dia.t_h2d cusp.dia.t_conv cusp.dia.t_kernel cusp.dia.t_d2h cusparse.gflops.cs-coo cusparse.gflops.cs-ell cusparse.gflops.cs-csr cusparse.gflops.cs-hyb cusparse.gflops.cs-hyb_mu cusparse.gflops.cs-bsr cusp.gflops.cu-coo cusp.gflops.cu-ell cusp.gflops.cu-csr cusp.gflops.cu-hyb cusp.gflops.cu-dia best.overall.rep best.cusparse.rep best.cusp.rep";
fi;
cols=$1;
filename=$2;

if ! [ -f "$filename" ]; then
    echo "ERROR: cannot open file $filename";
    exit 1;
fi;

count=1;
remove="";
for column in matrix group n_rows n_cols nnz_tot nnz_frac nnz_min nnz_max nnz_mu nnz_sigma nnzb_tot nnzb_min nnzb_max nnzb_mu nnzb_sigma snzb_min snzb_max snzb_mu snzb_sigma coord type cusparse.coo.conv_ok cusparse.coo.t_h2d cusparse.coo.t_conv cusparse.coo.t_kernel cusparse.coo.t_d2h cusparse.ell.conv_ok cusparse.ell.t_h2d cusparse.ell.t_conv cusparse.ell.t_kernel cusparse.ell.t_d2h cusparse.csr.conv_ok cusparse.csr.t_h2d cusparse.csr.t_conv cusparse.csr.t_kernel cusparse.csr.t_d2h cusparse.hyb.conv_ok cusparse.hyb.t_h2d cusparse.hyb.t_conv cusparse.hyb.t_kernel cusparse.hyb.t_d2h cusparse.hyb_mu.conv_ok cusparse.hyb_mu.t_h2d cusparse.hyb_mu.t_conv cusparse.hyb_mu.t_kernel cusparse.hyb_mu.t_d2h cusparse.bsr.conv_ok cusparse.bsr.t_h2d cusparse.bsr.t_conv cusparse.bsr.t_kernel cusparse.bsr.t_d2h cusp.coo.conv_ok cusp.coo.t_h2d cusp.coo.t_conv cusp.coo.t_kernel cusp.coo.t_d2h cusp.ell.conv_ok cusp.ell.t_h2d cusp.ell.t_conv cusp.ell.t_kernel cusp.ell.t_d2h cusp.csr.conv_ok cusp.csr.t_h2d cusp.csr.t_conv cusp.csr.t_kernel cusp.csr.t_d2h cusp.hyb.conv_ok cusp.hyb.t_h2d cusp.hyb.t_conv cusp.hyb.t_kernel cusp.hyb.t_d2h cusp.hyb.ellw cusp.dia.conv_ok cusp.dia.t_h2d cusp.dia.t_conv cusp.dia.t_kernel cusp.dia.t_d2h cusparse.gflops.cs-coo cusparse.gflops.cs-ell cusparse.gflops.cs-csr cusparse.gflops.cs-hyb cusparse.gflops.cs-hyb_mu cusparse.gflops.cs-bsr cusp.gflops.cu-coo cusp.gflops.cu-ell cusp.gflops.cu-csr cusp.gflops.cu-hyb cusp.gflops.cu-dia best.overall.rep best.cusparse.rep best.cusp.rep; do
    v=`echo "$cols" | grep "$column"`;
    if [ -z "$v" ]; then
	remove="$count,$remove";
    fi;
    count=$(($count+1));
done;
java -cp $WEKA_ABS_JAR_PATH weka.filters.unsupervised.attribute.Remove -i $filename  -R $remove;
