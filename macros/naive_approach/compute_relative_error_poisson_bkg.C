void compute_relative_error_poisson_bkg() {

///////////////////////////////////////////////////////////////////////////////
/// Variables                                                               ///
///////////////////////////////////////////////////////////////////////////////
	double CL = 0.68;   // Confidence level
	const Int_t n = 61; // Loop (number of days) 
	
	double e_bulk = 0.000536;       // efficiency of the bulk 
	double A_bulk = 2200 * 1e-6;    // Activity of the bulk (Bq/kg)
	double M_bulk = 7.00;           // Mass of the bulk
	
	double e_surface = 0.001616;    // efficiency of the surface
	double A_surface = 210 * 1e-6;  // Activity of the surface (Bq/kg)
	double M_surface = 0.880;       // Mass of the surface
	
	double e_trakcer = 0.067206;    // efficiency of the tracker 
	double A_tracker = 45.5 * 1e-3; // Activity of the tracker (Bq/kg)
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// Declaration of the TCanvas                                              ///
///////////////////////////////////////////////////////////////////////////////
	
	/// TOTAL NUMBER OF BACKGROUND (BULK + SURFACE) ///
	TCanvas *canvas_tot_bkg = new TCanvas("canvas_tot_bkg","Total background coming from the foil",200,10,700,500);
	canvas_tot_bkg->SetGrid();
	canvas_tot_bkg->DrawFrame(0,0,n,1000);
	
	/// TRACKER NUMBER OF EVENTS ///
	TCanvas *canvas_tracker = new TCanvas("canvas_tracker","Tracker (with background)",200,40,700,500);
	canvas_tracker->SetGrid();
	canvas_tracker->DrawFrame(0,0,n,17000);

	/// TRACKER RELATIVE ERROR ///
	TCanvas *canvas_tracker_relative_error = new TCanvas("canvas_tracker_re","Tracker Relative error (with background)",200,70,700,500);
	canvas_tracker_relative_error->SetGrid();
	canvas_tracker_relative_error->DrawFrame(0,0,n,1);
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// TRolke                                                                  ///
///////////////////////////////////////////////////////////////////////////////

	/// BULK ///   
 	TRolke *rolke_bulk = new TRolke();
	rolke_bulk->SetCL(CL);
	
	/// SURFACE ///
	TRolke *rolke_surface = new TRolke();
	rolke_surface->SetCL(CL);
	
	/// TRACKER ///
	TRolke *rolke_tracker = new TRolke();
	rolke_tracker->SetCL(CL);
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// Fill the graph                                                          ///
///////////////////////////////////////////////////////////////////////////////
	Int_t i;	
	Double_t x[n];
	Double_t y_bulk[n]   , ymin_bulk[n]   , ymax_bulk[n]    , ycenter_bulk[n];
	Double_t y_surface[n], ymin_surface[n], ymax_surface[n] , ycenter_surface[n];
	Double_t y_tot_bkg[n], ymin_tot_bkg[n], ymax_tot_bkg[n] , ycenter_tot_bkg[n];
	Double_t y_tracker[n], ymin_tracker[n], ymax_tracker[n] , ycenter_tracker[n];
	
	Double_t relative_error_tracker[n];
	
	for (i=0;i<n;i++)  {
	
		x[i] = i;
		
		y_bulk[i]    = e_bulk * A_bulk * M_bulk * 3600 * 24 * x[i];          /// Number of expected N after one day coming from the foil (bulk)
		y_surface[i] = e_surface * A_surface * M_surface * 3600 * 24 * x[i]; /// Number of expected N after one day coming from the foil (surface)
		y_tot_bkg[i] = y_bulk[i] + y_surface[i];                             /// Number of total events after one daycoming from the foil (bulk + surface)
		y_tracker[i] = e_trakcer * A_tracker * 3600 * 24 * x[i];             /// Number of expected N after one day coming from tracker

		if (y_tot_bkg[i] < 1)
		{
		rolke_tracker->SetKnownBkgBinomEff(y_tracker[i],20162,300000,0); /// 31791 evts selected on 300 000 evts generated (foil) bkg
		}
		
		if (y_tot_bkg[i] > 1)
		{
		rolke_tracker->SetPoissonBkgBinomEff(y_tracker[i],y_tot_bkg[i],20162,y_tracker[i]/y_tot_bkg[i],300000); /// 31791 evts selected on 300 000 evts generated (foil) bkg
		}
		//rolke_tracker->SetKnownBkgBinomEff(y_tracker[i],21791,300000,0);
		
		ymax_tracker[i] = (rolke_tracker->GetUpperLimit()) * e_trakcer;
		ymin_tracker[i] = (rolke_tracker->GetLowerLimit()) * e_trakcer;
				
		ycenter_tracker[i] =(ymax_tracker[i] + ymin_tracker[i]) / 2.00;
		
		//std::cout << "Bkg total = " << y_tot_bkg[i] << "  N signal = " << y_tracker[i] << "  N signal center = " << ycenter_tracker[i] << std::endl;
		
		if (y_tracker[i] != 0)  {
		
			relative_error_tracker[i] = (ymax_tracker[i] - ymin_tracker[i]) / ycenter_tracker[i];
			//std::cout << "Relative error = " << relative_error_tracker[i] << std::endl;
		}
	}
///////////////////////////////////////////////////////////////////////////////


	
///////////////////////////////////////////////////////////////////////////////
/// Declaration of the TGraph                                               ///
///////////////////////////////////////////////////////////////////////////////

      /// BULK NUMBER OF EVENTS ///
	TGraph *gr_bulk = new TGraph(n,x,y_bulk);
	TGraph *gr_surface = new TGraph(n,x,y_surface);
	TGraph *gr_tot_bkg = new TGraph(n,x,y_tot_bkg);
	
	/// TRACKER NUMBER OF EVENTS ///
	TGraph *gr_min_tracker    = new TGraph(n,x,ymin_tracker);
	TGraph *gr_max_tracker    = new TGraph(n,x,ymax_tracker);
	TGraph *gr_center_tracker = new TGraph(n,x,ycenter_tracker);
	TGraph *gr_cl_tracker     = new TGraph(2*n);
		
	/// TRACKER RELATIVE ERROR ///
	TGraph * gr_relative_error_tracker = new TGraph(n,x,relative_error_tracker);

	for (i=0;i<n;i++)  {
	
		gr_bulk->SetPoint(i,x[i],y_bulk[i]);
		gr_surface->SetPoint(i,x[i],y_surface[i]);
		gr_tot_bkg->SetPoint(i,x[i],y_tot_bkg[i]);
		gr_cl_tracker->SetPoint(i,x[i],ymax_tracker[i]);
		gr_cl_tracker->SetPoint(n+i,x[n-i-1],ymin_tracker[n-i-1]);
		gr_relative_error_tracker->SetPoint(n+i,x[n-i-1],relative_error_tracker[n-i-1]);
	}
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// OUTPUT                                                                  /// 
///////////////////////////////////////////////////////////////////////////////

	/// TOTAL NUMBER OF BACKGROUND (BULK + SURFACE) ///
	canvas_tot_bkg->cd();
	gr_bulk->SetLineWidth(3);
	gr_bulk->SetLineColor(kRed);
	gr_bulk->SetMarkerColor(kRed);
	gr_bulk->SetMarkerStyle(8);
	gr_bulk->GetXaxis()->SetTitle("Time of exposure [days]");
	gr_bulk->GetYaxis()->SetTitle("Number of expected events");
	gr_bulk->GetXaxis()->SetLabelSize(0.05);
	gr_bulk->GetYaxis()->SetLabelSize(0.05);
	gr_bulk->GetXaxis()->SetTitleSize(0.05);
	gr_bulk->GetYaxis()->SetTitleSize(0.05);
	gr_bulk->GetYaxis()->SetTitleOffset(1.3);
	gr_bulk->Draw("APL");
	
	gr_surface->SetLineWidth(3);
	gr_surface->SetLineColor(kBlue);
	gr_surface->SetMarkerColor(kBlue);
	gr_surface->SetMarkerStyle(8);
	gr_surface->Draw("PLsame");
	
	gr_tot_bkg->SetLineWidth(3);
	gr_tot_bkg->SetLineColor(kBlack);
	gr_tot_bkg->SetMarkerColor(kBlack);
	gr_tot_bkg->SetMarkerStyle(8);
	gr_tot_bkg->Draw("PLsame");
	
	TLegend * leg = new TLegend(0.5,0.8,0.8,0.9);
	leg->AddEntry(gr_surface,"Surface","l");
	leg->AddEntry(gr_bulk,"Bulk","l");
	leg->AddEntry(gr_tot_bkg,"Total","l");
	leg->Draw();
	
	/// BULK NUMBER OF EVENTS CANVAS ///
	canvas_tracker->cd();
	gr_cl_tracker->SetFillStyle(1001);
	gr_cl_tracker->SetFillColor(5);
	gr_cl_tracker->Draw("f");
	gr_min_tracker->Draw("l");
	gr_max_tracker->Draw("l");
	gr_center_tracker->SetLineWidth(2);
	gr_center_tracker->SetLineColor(1);
	gr_center_tracker->SetLineStyle(2);
	gr_center_tracker->SetMarkerColor(1);
	gr_center_tracker->SetMarkerStyle(7);
	gr_center_tracker->Draw("PC");
		
	/// TRACKER RELATIVE ERROR ///
	canvas_tracker_relative_error->cd();
	gr_relative_error_tracker->RemovePoint(0);
	gr_relative_error_tracker->SetLineWidth(3);
	gr_relative_error_tracker->SetMarkerColor(1);
	gr_relative_error_tracker->SetMarkerStyle(8);
	gr_relative_error_tracker->Draw("AP");
	gr_relative_error_tracker->GetXaxis()->SetTitle("Time of exposure [days]");
	gr_relative_error_tracker->GetYaxis()->SetTitle("Relative error");
	gr_relative_error_tracker->GetXaxis()->SetLabelSize(0.05);
	gr_relative_error_tracker->GetYaxis()->SetLabelSize(0.05);
	gr_relative_error_tracker->GetXaxis()->SetTitleSize(0.05);
	gr_relative_error_tracker->GetYaxis()->SetTitleSize(0.05);
	gr_relative_error_tracker->GetYaxis()->SetTitleOffset(1.3);
	
}

