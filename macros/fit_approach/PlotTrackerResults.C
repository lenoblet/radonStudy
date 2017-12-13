PlotTrackerResults()  {


	/////////////////////////////////////////////////////////////////////////
	/// Plot the mean activity w.r.t the exposure and its error           ///
	/////////////////////////////////////////////////////////////////////////
	TCanvas *c_tracker = new TCanvas("c_tracker","c_tracker",10,10,600,400);
	
	double x[] = {1, 
			  2,
			  3, 
			  4,
			  5,
			  6,
			  7,
			  8,
			  9,
			  10,
			  11,
			  12,
			  13,
			  14,
			  15,
			  16,
			  17,
			  18,
			  19,
			  20,
			  30,
			  40,
			  60,
			  70,
			  80,
			  90,
			  100};
			  
	double y[] = {0.0454878, 
			  0.0454324, 
			  0.0454901, 
			  0.0454731,
			  0.0454703,
			  0.0454921,
			  0.0454838,
			  0.0454845,
			  0.0454969,
			  0.0454883,
			  0.0454965,
			  0.0454901,
			  0.0454849,
			  0.0454947,
			  0.0454947,
			  0.0454957,
			  0.0454973,
			  0.045494,
			  0.0454975,
			  0.0454974,
			  0.0454966,
			  0.0454997,
			  0.0454966,
			  0.0454994,
			  0.0454987,
			  0.0454986,
			  0.0454988};

	double ex[] = {0,
			   0, 
			   0, 
			   0};
			   
	double ey[] = {1.24512e-05,
			   8.5582e-06,
			   6.94447e-06,
			   6.01215e-06,
			   5.3465e-06,
			   4.85287e-06,
			   4.50627e-06,
			   4.21171e-06,
			   3.97414e-06,
			   3.78552e-06,
			   3.58909e-06,
			   3.42217e-06,
			   3.30982e-06,
			   3.18546e-06,
			   3.05758e-06,
			   2.9666e-06,
			   2.88186e-06,
			   2.79865e-06,
			   2.72329e-06,
			   2.65795e-06,
			   2.16719e-06,
			   1.87404e-06,
			   1.54069e-06,
			   1.4283e-06,
			   1.3332e-06,
			   1.25519e-06,
			   1.19474e-06};
	
	TGraphErrors * gr_tracker_activity = new TGraphErrors(27, x, y, 0, ey);
	TGraph *gr = new TGraph(27,x,y);
	c_tracker->cd();
	c_tracker->SetGridx();
	c_tracker->SetGridy();
	gr->SetMarkerStyle(8);
	gr->SetLineStyle(2);
	gr->SetLineWidth(2);
	gr_tracker_activity->SetFillColor(5);
	gr_tracker_activity->Draw("AP3");
	gr->Draw("PL");
	gr_tracker_activity->GetXaxis()->SetTitle("Exposure [days]");
	gr_tracker_activity->GetYaxis()->SetTitle("Mean Activiy [Bq]");
	gr_tracker_activity->GetXaxis()->SetLabelSize(0.05);
	gr_tracker_activity->GetYaxis()->SetLabelSize(0.05);
	gr_tracker_activity->GetXaxis()->SetTitleSize(0.05);
	gr_tracker_activity->GetYaxis()->SetTitleSize(0.05);
	gr_tracker_activity->GetYaxis()->SetTitleOffset(1.4);
	c_tracker->Update();
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////////////
	/// Plot the relative error w.r.t the exposure                        ///
	/////////////////////////////////////////////////////////////////////////
	TGraph * gr_tracker_re = new TGraph("../../results/radon_in_tracker_chamber/tracker_results.txt","%lg %lg");

	TCanvas * c_re = new TCanvas("c_re","c_re",615,10,600,400);
	c_re->cd();
	c_re->SetGridx();
	c_re->SetGridy();
	c_re->SetLogx();
	
	gr_tracker_re->SetTitle("Relative error");
	gr_tracker_re->SetLineWidth(3);
	gr_tracker_re->SetMarkerColor(kRed);
	gr_tracker_re->SetLineColor(kRed);
	

	gr_tracker_re->GetXaxis()->SetTitle("Exposure [days]");
	gr_tracker_re->GetYaxis()->SetTitle("Relative Error [%]");
	gr_tracker_re->GetXaxis()->SetLabelSize(0.05);
	gr_tracker_re->GetYaxis()->SetLabelSize(0.05);
	gr_tracker_re->GetXaxis()->SetTitleSize(0.05);
	gr_tracker_re->GetYaxis()->SetTitleSize(0.05);
	gr_tracker_re->GetYaxis()->SetTitleOffset(0.9);
	gr_tracker_re->Draw("AL");
	TLegend * leg_1 = new TLegend(0.5,0.8,0.8,0.9);
	leg_1->AddEntry(gr_tracker_re,"Tracker","l");
	leg_1->Draw();
	c_re->Update();


	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////////////
	/// Plot the number of expected events w.r.t the exposure             ///
	/////////////////////////////////////////////////////////////////////////

	TCanvas * c_N = new TCanvas("c_N","c_N",10,440,600,400);

	TGraph * gr_bulk    = new TGraph();
	TGraph * gr_surface = new TGraph();
	TGraph * gr_tracker = new TGraph();
	//TGraph * gr_source  = new TGraph();

	double eff_bulk    = 0.0005;
	double eff_surface = 0.0016;
	double eff_tracker = 0.0672;

	double act_bulk    = 15.4e-3;
	double act_surface = 0.18e-3;
	double act_tracker = 45.5e-3;

	for (i_exposure = 1 ; i_exposure < 101 ; i_exposure ++ )  {
	
		double i_day     = i_exposure * 3600 * 24;
		double N_bulk    = eff_bulk    * act_bulk * i_day;
		double N_surface = eff_surface * act_surface * i_day;
		double N_tracker = eff_tracker * act_tracker * i_day;
		//double N_source  = N_surface + N_bulk;
		
		gr_bulk   ->SetPoint(i_exposure,i_exposure,N_bulk);
		gr_surface->SetPoint(i_exposure,i_exposure,N_surface);
		gr_tracker->SetPoint(i_exposure,i_exposure,N_tracker);
		//gr_source ->SetPoint(i_exposure,i_exposure,N_source);
	
	}
	
	c_N->cd();
	c_N->SetGridx();
	c_N->SetGridy();
	c_N->SetLogx();
	c_N->SetLogy();
	gr_tracker->SetLineColor(kRed);
	gr_bulk->SetLineColor(kBlack);
	gr_surface->SetLineColor(kBlue);
	//gr_source->SetLineColor(kGreen);
	
	gr_tracker->SetLineWidth(2);
	gr_bulk->SetLineWidth(2);
	gr_surface->SetLineWidth(2);
	//gr_source->SetLineWidth(2);

	gr_tracker->Draw();
	gr_bulk->Draw("same");
	gr_surface->Draw("same");
	//gr_source->Draw("same");
	
	gr_tracker->GetXaxis()->SetTitle("Exposure [days]");
	gr_tracker->GetYaxis()->SetTitle("Number of expected events");
	gr_tracker->GetXaxis()->SetLabelSize(0.05);
	gr_tracker->GetYaxis()->SetLabelSize(0.05);
	gr_tracker->GetXaxis()->SetTitleSize(0.05);
	gr_tracker->GetYaxis()->SetTitleSize(0.05);
	gr_tracker->GetYaxis()->SetTitleOffset(0.9);
	gr_tracker->GetXaxis()->SetRangeUser(2,105);
	gr_tracker->GetYaxis()->SetRangeUser(0.001,100000);

	TLegend * leg_2 = new TLegend(0.5,0.8,0.8,0.9);
	leg_2->AddEntry(gr_tracker,"Tracker","l");
	//leg_2->AddEntry(gr_source,"Source (bulk + surface)","l");
	leg_2->AddEntry(gr_bulk,"Bulk","l");
	leg_2->AddEntry(gr_surface,"Surface","l");
	leg_2->Draw();
	c_N->Update();
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////

}
