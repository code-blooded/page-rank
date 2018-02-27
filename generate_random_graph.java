package com.company;

//including import
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

//class to generate random graph
class random_graph {
    public int nodes;
    private List connected;
    private List unconnected;
    private PrintWriter writer;

    //contructor
    random_graph(int n){
        nodes = n;
        connected = new ArrayList();
        unconnected = new ArrayList();
        connected.add(1);
        for (int i = 2; i <= nodes; i++) {
            unconnected.add(i); //initializing unconected to all nodes excepts 1
        }
        try {
            writer = new PrintWriter("the-file-name.txt", "UTF-8"); //the file the output is written to
        }catch (Exception e) {
            System.out.println("File Error");   //file error
        }
    }

    //function to generate the given percentage of edges and nodes
    void generate(double percentage){
        int extra_edges,edges;
        extra_edges = (int)(nodes*nodes*(percentage/100.0));
        System.out.println(extra_edges);
        edges = 0;
        Random R = new Random(4587);
        while(!unconnected.isEmpty()){  //as long as a node is disconnected
            int temp1 = R.nextInt(connected.size());
            int temp2 = R.nextInt(unconnected.size());
            int u = (int)connected.get(temp1);
            int v = (int)unconnected.get(temp2);
            addEdge(u,v);   //add randomly choosen nodes edge
            unconnected.remove(temp2);
            connected.add(v);
            edges++;
        }
        while(extra_edges>0){   //adding the extra percentage
            int temp1 = R.nextInt(nodes);
            int temp2 = R.nextInt(nodes);
            addEdge(temp1,temp2);
            extra_edges--;
        }
        writer.close();
    }
    //purely for testing purpose
    void addEdge(int u,int v){
        //System.out.println(u+" "+v);
        writer.println(u+" "+v);
    }
}

public class generate_random_graph {
    //driver function
    public static void main(String[] args) {
        //creating a graph obj of 1000 nodes
        random_graph g = new random_graph(1000);
        //generate a max of (0.1*nodes*nodes/100)% edges
        g.generate(0.1);
    }
}
