###############################################################################
# Date   : jan 2016                                                           #
# Author : Le Noblet Thibaud (lenoblet@lapp.in2p3.fr)                         #
###############################################################################
# Description : This directory contains all the different macros used in the  #
#               studies. The inputs are the histos coming from falaise.       #
#               2 approachs have been tested :                                #
#                                                                             #
#                 - naive approach : compute the level of radon just by       #
#                 computing the number of expected events according the       #
#                 exposure. 3 models of bkg are tested (no bkg, bkg known,    #
#                 the bkg is poissonian). This approach don't work if S/B is  #
#                 too low.                                                    #
#                                                                             #
#                 - fit approach : a more matured approach using the length   #
#                 of the alpha track to determine the different activies.     #
#                 All the macros used in this approach are described below.   #
#                                                                             #
# List of the macros :                                                        #
#   - Sum_pdf : Sum the 3 contributions (bulk,surface,tracker) and            #
#     normalize to their activities. Create the histo_alpha_length.root       #
#     First step of the study                                                 #
#                                                                             #
#   - Radon_in_tracker_chamber : Fit the alpha track length pdf with the 3    #
#     contributions to get the activity of the tracker (precise)              #
#     Second step of the study                                                #
#                                                                             #
#   - Radon_on_source_foil : Fit the alpha track length pdf with the 3        #
#     contributions to get the activities coming from the 3 contributions     #
#                                                                             #
#   - PlotTrackerResults : Get the results and plot them for the tracker      #
#     selection                                                               #
#                                                                             #
#   - PlotSourceResults : Get the results and plot them for the source        #
#     selection                                                               #
#                                                                             #
#   - ExampleFit : Obtain the fit of a pseudo experiment                      #
###############################################################################
