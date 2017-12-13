PlotSourceResults()  {


	/////////////////////////////////////////////////////////////////////////
	/// Plot the mean activity w.r.t the exposure and its error           ///
	/////////////////////////////////////////////////////////////////////////
	TCanvas *c_activity_tracker = new TCanvas("c_activity","c_activity",10,10,600,400);
	
	double x_tracker[] = {1, 
			   	    2,
			  	    3, 
			  	    4,
			  	    5,
			  	    6,
			  	    7,
			  	    8,
			  	    9,
			  	    10};
			  
	double y_tracker[] = {0.045092,
			  	    0.0454085,
 				    0.0454744,
 				    0.0454018,
				    0.0454452,
				    0.0454985,
				    0.0454414,
				    0.045458,
				    0.0454912,
				    0.0455087};
			  
			  
	double ex[] = {0,
			   0, 
			   0, 
			   0};
			   
	double ey_tracker[] = {2.68631e-05,
				     1.80689e-05,
				     1.47163e-05,
				     1.2729e-05,
				     1.13839e-05,
				     1.05904e-05,
				     9.73313e-06,
				     9.12548e-06,
				     8.60184e-06,
		     		     8.13466e-06};
	
	TGraphErrors * gr_tracker_activity = new TGraphErrors(10, x_tracker, y_tracker, 0, ey_tracker);
	TGraph *gr_trac_act = new TGraph(10,x_tracker,y_tracker);
	c_activity_tracker->cd();
	c_activity_tracker->SetGridx();
	c_activity_tracker->SetGridy();
	gr_trac_act->SetMarkerStyle(8);
	gr_trac_act->SetLineStyle(2);
	gr_trac_act->SetLineWidth(2);
	gr_tracker_activity->SetFillColor(5);
	gr_tracker_activity->Draw("AP3");
	gr_trac_act->Draw("PL");
	gr_tracker_activity->GetXaxis()->SetTitle("Exposure [days]");
	gr_tracker_activity->GetYaxis()->SetTitle("Mean Activiy [Bq]");
	gr_tracker_activity->GetXaxis()->SetLabelSize(0.05);
	gr_tracker_activity->GetYaxis()->SetLabelSize(0.05);
	gr_tracker_activity->GetXaxis()->SetTitleSize(0.05);
	gr_tracker_activity->GetYaxis()->SetTitleSize(0.05);
	gr_tracker_activity->GetYaxis()->SetTitleOffset(1.6);
	gr_tracker_activity->GetYaxis()->SetRangeUser(0.0450,0.0457);
	c_activity_tracker->Update();
	
	
	///
	TCanvas *c_activity_bulk = new TCanvas("c_bulk","c_bulk",615,10,600,400);
	
	double x_bulk[] = {1, 
			  2,
			  3, 
			  4,
			  5,
			  6,
			  7,
			  8,
			  9,
			  10};
			  
	double y_bulk[] = {0.0153063,
				 0.0153609,
				 0.0153989,
				 0.0153651,
				 0.015385,
				 0.0153893, 
				 0.015373,
				 0.0153913, 
				 0.0153889,
				 0.0153975};
			  
	double ex[] = {0,
			   0, 
			   0, 
			   0};
			   
	double ey_bulk[] = {1.24364e-05,
				  8.56567e-06,
				  6.97503e-06,
				  6.03342e-06,
			        5.40135e-06,
				  5.01457e-06,
				  4.61898e-06,
				  4.33192e-06,
				  4.0735e-06,
				  3.86311e-06};
	
	TGraphErrors * gr_bulk_activity = new TGraphErrors(10, x_bulk, y_bulk, 0, ey_bulk);
	TGraph *gr_bulk_act = new TGraph(10,x_bulk,y_bulk);
	c_activity_bulk->cd();
	c_activity_bulk->SetGridx();
	c_activity_bulk->SetGridy();
	gr_bulk_act->SetMarkerStyle(8);
	gr_bulk_act->SetLineStyle(2);
	gr_bulk_act->SetLineWidth(2);
	gr_bulk_activity->SetFillColor(5);
	gr_bulk_activity->Draw("AP3");
	gr_bulk_act->Draw("PL");
	gr_bulk_activity->GetXaxis()->SetTitle("Exposure [days]");
	gr_bulk_activity->GetYaxis()->SetTitle("Mean Activiy [Bq]");
	gr_bulk_activity->GetXaxis()->SetLabelSize(0.05);
	gr_bulk_activity->GetYaxis()->SetLabelSize(0.05);
	gr_bulk_activity->GetXaxis()->SetTitleSize(0.05);
	gr_bulk_activity->GetYaxis()->SetTitleSize(0.05);
	gr_bulk_activity->GetYaxis()->SetTitleOffset(1.6);
	gr_bulk_activity->GetYaxis()->SetRangeUser(0.01520,0.0155);
	c_activity_bulk->Update();
	
	
	///
	TCanvas *c_activity_surface = new TCanvas("c_surface","c_surface",1225,10,600,400);
	
	double x_surface[] = {1, 
			  2,
			  3, 
			  4,
			  5,
			  6,
			  7,
			  8,
			  9,
			  10};
			  
	double y_surface[] = {0.000210673,
				    0.000187844,
				    0.000184931,
				    0.000185061,
				    0.000184911,
				    0.000183983,
				    0.000185394,
				    0.000184308,
				    0.000184631,
				    0.000184346}
			  
	double ex[] = {0,
			   0, 
			   0, 
			   0};
			   
	double ey_surface[] = {2.02791e-06,
				     1.42411e-06,
				     1.15314e-06,
				     9.9209e-07,
				     8.88984e-07,
				     8.24999e-07,
				     7.59411e-07,
				     7.10623e-07,
				     6.72884e-07,
				     6.36755e-07};
	
	TGraphErrors * gr_surface_activity = new TGraphErrors(10, x_surface, y_surface, 0, ey_surface);
	TGraph *gr_surface_act = new TGraph(10,x_surface,y_surface);
	c_activity_surface->cd();
	c_activity_surface->SetGridx();
	c_activity_surface->SetGridy();
	gr_surface_act->SetMarkerStyle(8);
	gr_surface_act->SetLineStyle(2);
	gr_surface_act->SetLineWidth(2);
	gr_surface_activity->SetFillColor(5);
	gr_surface_activity->Draw("AP3");
	gr_surface_act->Draw("PL");
	gr_surface_activity->GetXaxis()->SetTitle("Exposure [days]");
	gr_surface_activity->GetYaxis()->SetTitle("Mean Activiy [Bq]");
	gr_surface_activity->GetXaxis()->SetLabelSize(0.05);
	gr_surface_activity->GetYaxis()->SetLabelSize(0.05);
	gr_surface_activity->GetXaxis()->SetTitleSize(0.05);
	gr_surface_activity->GetYaxis()->SetTitleSize(0.05);
	gr_surface_activity->GetYaxis()->SetTitleOffset(1.6);
	gr_surface_activity->GetYaxis()->SetRangeUser(0.000175,0.00022);
	c_activity_surface->Update();
	
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	
	
	/////////////////////////////////////////////////////////////////////////
	/// Plot the relative error w.r.t the exposure                        ///
	/////////////////////////////////////////////////////////////////////////
	TGraph * gr_bulk_re    = new TGraph("../../results/radon_on_source_foil/bulk_results.txt","%lg %lg");
	TGraph * gr_surface_re = new TGraph("../../results/radon_on_source_foil/surface_results.txt","%lg %lg");
	//TGraph * gr_surface_re = new TGraph("/home/lenoblet-local/work/bi214_measurement/macros/NEMO3Ana-master/macro/surface_results.txt","%lg %lg");
	//TGraph * gr_tracker_re = new TGraph("../../results/radon_on_source_foil/tracker_results.txt","%lg %lg"); <- this one is correct
	TGraph * gr_tracker_re = new TGraph("../../results/radon_in_tracker_chamber/tracker_results.txt","%lg %lg");
	TCanvas * c_re = new TCanvas("c_re","c_re",615,440,600,400);
	c_re->cd();
	c_re->SetGridx();
	c_re->SetGridy();
	c_re->SetLogx();
	
	gr_tracker_re->SetTitle("Relative error");
	gr_tracker_re->SetLineWidth(3);
	gr_tracker_re->SetMarkerColor(kRed);
	gr_tracker_re->SetLineColor(kRed);
	
	gr_bulk_re->SetLineWidth(3);
	gr_bulk_re->SetLineColor(kBlack);
	
	gr_surface_re->SetLineWidth(3);
	gr_surface_re->SetLineColor(kBlue);
	double xReturn =0;
	double yReturn =0;
	for (int i = 0 ; i < 101 ; i++)  {
		double Nsurface = gr_surface_re->GetPoint(i,xReturn,yReturn);
		//std::cout << "Here : " << yReturn << std::endl;
		
		if (yReturn > 100)  {
		
			gr_surface_re->SetPoint(i,xReturn,100);
		}
	}
	
	gr_surface_re->GetXaxis()->SetTitle("Exposure [days]");
	gr_surface_re->GetYaxis()->SetTitle("Relative Error [%]");
	gr_surface_re->GetXaxis()->SetLabelSize(0.05);
	gr_surface_re->GetYaxis()->SetLabelSize(0.05);
	gr_surface_re->GetXaxis()->SetTitleSize(0.05);
	gr_surface_re->GetYaxis()->SetTitleSize(0.05);
	gr_surface_re->GetYaxis()->SetTitleOffset(0.9);
	gr_surface_re->GetYaxis()->SetRangeUser(0,90);
	gr_surface_re->Draw("AL");
	gr_tracker_re->Draw("L");
	gr_bulk_re->Draw("L");
	TLegend * leg_1 = new TLegend(0.5,0.8,0.8,0.9);
	leg_1->AddEntry(gr_tracker_re,"Tracker","l");
	leg_1->AddEntry(gr_bulk_re,"Bulk","l");
	leg_1->AddEntry(gr_surface_re,"Surface","l");
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

	double eff_bulk    = 0.0294;
	double eff_surface = 0.1007;
	//double eff_tracker = 0.0159;
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
	gr_tracker->GetYaxis()->SetRangeUser(0.1,100000);

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
