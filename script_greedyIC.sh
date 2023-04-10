#!/bin/bash

export PATH_TO_TSS_INSTANCES=TSS-instances

executable=greedyIC_exe7
file_name=output_greedyIC7

rm -rf $file_name
mkdir $file_name

files=("graph_dolphins.dimacs" "graph_karate.dimacs" "graph_football.dimacs" "graph_jazz.dimacs" "socfb-nips-ego.dimacs" "socfb-Mich67.dimacs" "socfb-Brandeis99.dimacs" "ego-facebook.dimacs" "graph_CA-GrQc.dimacs" "graph_ncstrlwg2.dimacs" "graph_CA-HepTh.dimacs" "graph_actors_dat.dimacs" "graph_CA-HepPh.dimacs" "graph_CA-AstroPh.dimacs" "graph_CA-CondMat.dimacs" "soc-gplus.dimacs" "graph_Email-Enron.dimacs" "musae_git.dimacs" "gemsec_facebook_artist.dimacs" "deezer_HR.dimacs" "loc-gowalla_edges.dimacs" "Amazon0302.dimacs" "com-dblp.ungraph.dimacs")

# Get the total number of files to process
total_files=${#files[@]}

# Initialize a counter for the progress bar
counter=0

for file in "${files[@]}"; do
    # Increment the counter
    ((counter++))

    # Calculate the percentage of completion
    percent=$((counter * 100 / total_files))

    # Update the progress bar
    bar=$(printf '#%.0s' $(seq 1 $((percent / 2))))
    printf "\r[%-50s] %d%%" "$bar" $percent

    filename=$(basename -- "$file")
    extension="${filename##*.}"
    filename="${filename%.*}"
    
    echo -e "\nThe file being executed is: " $filename

    # Execute the command and redirect the output to a file in the output directory
    ./$executable $PATH_TO_TSS_INSTANCES/"$file" > "$file_name/$filename.salida"
done

