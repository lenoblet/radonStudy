#!/usr/bin/python
###############################################################################
### Description                                                             ###
# Date   : 23/10/15                                                         ###
# Author : Le Noblet Thibaud (lenoblet@lapp.in2p3.fr)                       ###
# Get the histograms :                                                      ###
# 	- source strips surface                                               ###   
# 	- source strips bulk                                                  ###
# 	- tracker volume                                                      ###
# Sum the 3 histos and normalized then to a their given activity            ###
###############################################################################



###############################################################################
### Import                                                                  ###
###############################################################################
from ROOT import *
###############################################################################



###############################################################################
### Get file and histos total                                               ###
###############################################################################
#FILE_source_strips_bulk    = TFile.Open("../../histos/1e1a_events_source_selection/histo_alpha_length_bulk_1M.root","READ")
#FILE_source_strips_surface = TFile.Open("../../histos/1e1a_events_source_selection/histo_alpha_length_surface_1M.root","READ")
#FILE_source_strips_tracker = TFile.Open("../../histos/1e1a_events_source_selection/histo_alpha_length_tracker_1M.root","READ")

FILE_source_strips_bulk    = TFile.Open("../../histos/1e1a_events_tracker_selection/histo_alpha_length_bulk_300m.root","READ")
FILE_source_strips_surface = TFile.Open("../../histos/1e1a_events_tracker_selection/histo_alpha_length_surface_300m.root","READ")
FILE_source_strips_tracker = TFile.Open("../../histos/1e1a_events_tracker_selection/histo_alpha_length_tracker_300m.root","READ")

histo_source_strips_bulk    = FILE_source_strips_bulk.Get("alpha_length_50")
histo_source_strips_surface = FILE_source_strips_surface.Get("alpha_length_50")
histo_source_strips_tracker = FILE_source_strips_tracker.Get("alpha_length_50")

histo_source_strips_bulk_normalized    = histo_source_strips_bulk.Clone("histo_source_strips_bulk_normalized")
histo_source_strips_surface_normalized = histo_source_strips_surface.Clone("histo_source_strips_surface_normalized")
histo_source_strips_tracker_normalized = histo_source_strips_tracker.Clone("histo_source_strips_tracker_normalized")
###############################################################################



###############################################################################
### Normalize the histograms to their activy                                ###
###############################################################################
histo_source_strips_bulk_normalized.Scale(15.4*1e-3)        # Activity bulk
histo_source_strips_surface_normalized.Scale(0.185*1e-3)    # Activity surface
histo_source_strips_tracker_normalized.Scale(45.5*1e-3)     # Activity tracker

histo_bulk_norm    = histo_source_strips_bulk_normalized.Clone("histo_bulk_norm")
histo_surface_norm = histo_source_strips_surface_normalized.Clone("histo_surface_norm")
histo_tracker_norm = histo_source_strips_tracker_normalized.Clone("histo_tracker_norm")


###############################################################################
### Add the histograms                                                      ###
###############################################################################
histo_tot = histo_bulk_norm.Clone("histo_tot")
histo_tot.Add(histo_surface_norm)
histo_tot.Add(histo_tracker_norm)



###############################################################################
### Take into account the efficiency of the 1e1a selection                  ###
###############################################################################
histo_tot_norm_day = histo_tot.Clone("histo_tot_norm_day")
#histo_tot_norm_day.Scale((3600*24)/1000000.)
histo_tot_norm_day.Scale((3600*24)/300000.)
###############################################################################



###############################################################################
### Creation and organisation of the ROOT file                              ### 
###############################################################################
#histo_file = TFile("../../histos/1e1a_events_source_selection/histo_alpha_length.root","recreate")
histo_file = TFile("../../histos/1e1a_events_tracker_selection/histo_alpha_length.root","recreate")

histo_file.mkdir("fake_data")
histo_file.mkdir("bulk")
histo_file.mkdir("surface")
histo_file.mkdir("tracker")

histo_file.cd("fake_data")
histo_tot_norm_day.SetName("fake_data_AlphaTrackLength")
histo_tot_norm_day.Write()

histo_file.cd("bulk")
alpha_track_length = histo_source_strips_bulk.Clone()
alpha_track_length.SetName("bulk_AlphaTrackLength")
alpha_track_length.Write()

histo_file.cd("surface")
alpha_track_length = histo_source_strips_surface.Clone()
alpha_track_length.SetName("surface_AlphaTrackLength")
alpha_track_length.Write()

histo_file.cd("tracker")
alpha_track_length = histo_source_strips_tracker.Clone()
alpha_track_length.SetName("tracker_AlphaTrackLength")
alpha_track_length.Write()

print "The file histo_alpha_length.root has been created"
###############################################################################
raw_input ("wait")

