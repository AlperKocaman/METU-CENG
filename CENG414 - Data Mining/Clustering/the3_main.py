import sys
from the3_agglomerative_clustering import AgglomerativeClustering
from the3_agglomerative_clustering import read_input_file

def sort_clusters(clusters_to_be_sorted):
    sorted_clusters=[]
    sorted_clusters=[sorted(item, key=lambda tup: tup[0]) for item in clusters_to_be_sorted]
    sorted_clusters.sort()
    return sorted_clusters

    
def main():
    if len(sys.argv) < 2:
        print("Usage: python the3_main.py <input_file_name>")

    else:
        out_file=open("sample_output.txt","w+")
        input_file = sys.argv[1]
        input_data=read_input_file(input_file)
        out_file.write("Input data\n")
        out_file.write(str(input_data)+'\n')
        out_file.write("-----------------------------------------\n")

        #Test 1
        model = AgglomerativeClustering(input_data)
        model.initialize_clustering()
        out_file.write("Initial clusters\n")
        out_file.write(str(model.clusters_current)+'\n')
        out_file.write("-----------------------------------------\n")

        number_of_clusters=2
        clusters=model.fit_predict(number_of_clusters,AgglomerativeClustering.LINKAGE['MIN'])
        clusters=sort_clusters(clusters)
        out_file.write("Test1"+'\n')
        out_file.write(str(clusters)+'\n')
        out_file.write("-----------------------------------------\n")
        
        #Test 2
        model = AgglomerativeClustering(input_data)
        model.initialize_clustering()
        number_of_clusters=3
        clusters=model.fit_predict(number_of_clusters,AgglomerativeClustering.LINKAGE['MAX'])
        clusters=sort_clusters(clusters)        
        out_file.write("Test2"+'\n')
        out_file.write(str(clusters)+'\n')
        out_file.write("-----------------------------------------\n")
        
        #Test 3
        model = AgglomerativeClustering(input_data)
        model.initialize_clustering()
        number_of_clusters=3
        clusters=model.fit_predict(number_of_clusters,AgglomerativeClustering.LINKAGE['GROUP_AVG'])
        clusters=sort_clusters(clusters) 
        out_file.write("Test3"+'\n')
        out_file.write(str(clusters)+'\n')
        out_file.write("-----------------------------------------\n")     
        
        # You can implement your own tests here.
        # This file is not going to be used for evaluation.

if __name__ == "__main__":
    main()
