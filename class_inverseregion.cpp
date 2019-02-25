#include "class_inverseregion.h"

class_inverseregion::class_inverseregion(class_region &region, const int &border_extrap){
    // Note that border_extrap must be greater than or equal to 1.
    // Form inverseregion given a region input
    // Allocate space for region - note that upperbound of width will be width of the region + 2
    alloc(region.nodelist.height+2*border_extrap,region.nodelist.width+2);

    // Set bounds - relative to new mat_plot_extrap array
    upperbound = 0;
    lowerbound = region.lowerbound-region.upperbound+2*border_extrap;
    leftbound = 0;
    rightbound = region.rightbound-region.leftbound+2*border_extrap;

    // Find new nodes ---------------------------------------------------//
    // Left nodes: border_extrap space doesnt interact with previous nodes, so just add them
    for (int i=0; i<border_extrap; i++) {
        // Nodelist
        nodelist.value[i] = 0; // Top node
        nodelist.value[i+nodelist.height] = lowerbound; // Bottom Node

        // Noderange
        noderange.value[i] = 2;

        // totalpoints
        totalpoints += (nodelist.value[i+nodelist.height]-nodelist.value[i])+1;
    }

    // Middle nodes: middle nodes will interact with region nodes
    for (int i=border_extrap; i<nodelist.height-border_extrap; i++) {
        if (region.noderange.value[i-border_extrap] > 1) {
            // First node pair
            nodelist.value[i] = 0;
            nodelist.value[i+nodelist.height] = region.nodelist.value[i-border_extrap]-region.upperbound+border_extrap-1;

            // totalpoints
            totalpoints += (nodelist.value[i+nodelist.height]-nodelist.value[i]+1);

            // Middle node pairs
            for (int j=0; j<region.noderange.value[i-border_extrap]-2; j+=2) {
                // Nodelist
                nodelist.value[i+(j+2)*nodelist.height] = region.nodelist.value[(i-border_extrap)+(j+1)*region.nodelist.height]-region.upperbound+border_extrap+1;
                nodelist.value[i+(j+3)*nodelist.height] = region.nodelist.value[(i-border_extrap)+(j+2)*region.nodelist.height]-region.upperbound+border_extrap-1;

                // totalpoints
                totalpoints += (nodelist.value[i+(j+3)*nodelist.height]-nodelist.value[i+(j+2)*nodelist.height])+1;
            }

            // Last node pair
            nodelist.value[i+region.noderange.value[i-border_extrap]*nodelist.height] = region.nodelist.value[(i-border_extrap)+(region.noderange.value[i-border_extrap]-1)*region.nodelist.height]-region.upperbound+border_extrap+1;
            nodelist.value[i+(region.noderange.value[i-border_extrap]+1)*nodelist.height] = lowerbound;

            // totalpoints
            totalpoints += (nodelist.value[i+(region.noderange.value[i-border_extrap]+1)*nodelist.height]-nodelist.value[i+region.noderange.value[i-border_extrap]*nodelist.height])+1;

            // Noderange
            noderange.value[i] = region.noderange.value[i-border_extrap]+2;
        } else {
            // Nodelist
            nodelist.value[i] = 0;
            nodelist.value[i+nodelist.height] = lowerbound;

            // Noderange
            noderange.value[i] = 2;

            // totalpoints
            totalpoints += (nodelist.value[i+nodelist.height]-nodelist.value[i])+1;
        }
    }

    // Right nodes: border_extrap space doesnt interact with previous nodes, so just add them
    for (int i=nodelist.height-border_extrap; i<nodelist.height; i++) {
        // Nodelist
        nodelist.value[i] = 0; // Top node
        nodelist.value[i+nodelist.height] = lowerbound; // Bottom Node

        // Noderange
        noderange.value[i] = 2;

        // totalpoints
        totalpoints += (nodelist.value[i+nodelist.height]-nodelist.value[i])+1;
    }
}
