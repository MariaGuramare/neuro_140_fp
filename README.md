# neuro_140_fp
Neuro 140 : Biological and Artificial Intelligence
Final project - Maria Guramare
Clustering protein data from viruses : Experimenting with statistical methods and unsupervised learning


# goal
This project contains code to :
  1 - Retrive 3D coordinates from PDB files
  2 - Compute 
      a - A measure of density : randomly sample a fixed proportion of pairs of amino acids and compute an average of their Euclidean distance in the 3D space
      b - The convex hull of the 3D conformation, and retrieve the proportion of total amino acids which constitute the convex hull
      c - The volume of the 3D conformation based on its convex hull
  3 - Perform an unsupervised machine learning technique : k-means clustering.  
The goal of this project was to experiment with various features of the 3D conformation of viral proteins, and try to look for ways to identify the different categories using features extracted from their 3D conformations.
I also wanted to test the efficiency of k-means in picking up clusters which are very close, and to assess the worth of using simulated annealing instead of randomness in picking initial clusteroids. 
  
  
# Part 1 - C++ - data_processing.cpp
usage : ./data_processing infile infile_names num_prts outfile_stats
The infile needs to be formatted as information from a .xml file downloaded from the PDB library, with the data contained between the "<PDBx:atom_siteCategory>" tags. Every protein in the file has to be preceded by "new prot" on a seperate line and terminated by "end prot" on a seperate line.
The program :
  1) separates every protein found into a separate .txt file containing 3D coordinates (3 numbers per line), naming each file according to the names found in infile_names ;
  2) outputs a file with statistics with the measure of density explained in 2a here above.
  
# Part 2 - Matlab - convex_hull.m
The program imports the files with 3D coordinates created in part 1, and for each protein computes the convex hull.
Then it outputs to the same statistics file :
  1) the percentage of amino acids of the protein that lay on the convex hull ; 
  2) the volume of the 3D shape formed by the coordinates of the protein, based on the convex hull.

# Part 3 - Jupyter notebook
This part is the main part of the project. The previous two parts essentially serve to preprocess the raw protein data in order to obtain 3 values per protein, which we then use for k-means clustering.
Everything the code can achieve can be observed by simply running the entire script.
The script performs various variations of k-means on these 3 values per protein :
  - classic k-means or optimized k-means by choosing initial clusters using simulated annealing
  - clustering with k=3 or k=4 (rationale behind chosing those values explained in the report)
  - clustering on the original data or on a data from which outliers were removed

All outputs of the various forms of clustering can be found in the "results" folder.
