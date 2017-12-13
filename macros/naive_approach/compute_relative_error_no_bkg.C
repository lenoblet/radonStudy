void compute_relative_error_no_bkg()  {

///////////////////////////////////////////////////////////////////////////////
/// Variables                                                               ///
///////////////////////////////////////////////////////////////////////////////
	int    N_bkg   = 0;             // Number of bkg
	const  Int_t n = 61;            // Loop from 0 to 31
	double CL      = 0.68;          // Confidence level
	
	double e_bulk = 0.000536;       // efficiency of the bulk (300 000 evts generated in MC)
	double A_bulk = 2200 * 1e-6;    // Activity of the bulk (Bq/kg)
	double M_bulk = 7.00;           // Mass of the bulk
	
	double e_surface = 0.001616;    // efficiency of the surface (300 000 evts generated in MC)
	double A_surface = 210 * 1e-6;  // Activity of the surface (Bq/kg)
	double M_surface = 0.880;       // Mass of the surface
	
	double e_tracker = 0.067206;    // efficiency of the tracker (300 000 evts generated in MC)
	double A_tracker = 45.5 * 1e-3; // Activity of the tracker (Bq/kg)
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// Declaration of the TCanvas                                              /// 
///////////////////////////////////////////////////////////////////////////////

  /// BULK NUMBER OF EVENTS ///
	TCanvas *canvas_bulk = new TCanvas("canvas_bulk","Bulk (no background)",200,10,700,500);
	canvas_bulk->SetGrid();
	canvas_bulk->DrawFrame(0,0,n,100);
	
	/// SURFACE NUMBER OF EVENTS ///
	TCanvas *canvas_surface = new TCanvas("canvas_surface","Surface (no background)",200,10,700,500);
	canvas_surface->SetGrid();
	canvas_surface->DrawFrame(0,0,n,3);
	
	/// TRACKER NUMBER OF EVENTS ///
	TCanvas *canvas_tracker = new TCanvas("canvas_tracker","Tracker (no background)",200,10,700,500);
	canvas_tracker->SetGrid();
	canvas_tracker->DrawFrame(0,0,n,17000);
	
	/// TRACKER RELATIVE ERROR ///
	TCanvas *canvas_tracker_relative_error = new TCanvas("canvas_tracker_re","Tracker Relative error (no background)",200,10,700,500);
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
/// Fill the Graph                                                          ///
///////////////////////////////////////////////////////////////////////////////
  Int_t i;
	
	Double_t x[n];
	Double_t y_bulk[n]   , ymin_bulk[n]   , ymax_bulk[n];
	Double_t y_surface[n], ymin_surface[n], ymax_surface[n];
	Double_t y_tracker[n], ymin_tracker[n], ymax_tracker[n];
	
	Double_t relative_error_tracker[n];
	 
	for (i=0;i<n;i++)  {
	
		x[i] = i;
		/// BULK ///
		y_bulk[i] = e_bulk * A_bulk * M_bulk * 3600 * 24 * x[i];      /// Number of expected N after one day coming from the foil (bulk)
		rolke_bulk->SetKnownBkgBinomEff(y_bulk[i],161,300000,N_bkg);  /// 289 evts selected on 300 000 evts generated
		ymax_bulk[i] = (rolke_bulk->GetUpperLimit()) * e_bulk;
		ymin_bulk[i] = (rolke_bulk->GetLowerLimit()) * e_bulk;
		
		/// SURFACE ///
		y_surface[i] = e_surface * A_surface * M_surface * 3600 * 24 * x[i];  /// Number of expected N after one day coming from the foil (surface)
		rolke_surface->SetKnownBkgBinomEff(y_surface[i],485,300000,N_bkg);    /// 665 evts selected on 300 000 evts generated
		ymax_surface[i] = (rolke_surface->GetUpperLimit()) * e_surface;
		ymin_surface[i] = (rolke_surface->GetLowerLimit()) * e_surface;
		
		/// TRACKER ///
		y_tracker[i] = e_tracker * A_tracker * 3600 * 24 * x[i];             /// Number of expected N after one day coming from the tracker
		rolke_tracker->SetKnownBkgBinomEff(y_tracker[i],20162,300000,N_bkg); /// 21791 evts selected on 300 000 evts generated
		ymax_tracker[i] = (rolke_tracker->GetUpperLimit()) * e_tracker;
		ymin_tracker[i] = (rolke_tracker->GetLowerLimit()) * e_tracker;
		
		if (y_tracker[i] != 0)  {
		
			relative_error_tracker[i] = (ymax_tracker[i] - ymin_tracker[i]) / y_tracker[i];
		}
		
		//std::cout << "N signal = " << y_tracker[i] << "  N signal center = " << (ymax_tracker[i] + ymin_tracker[i])/2.00 << std::endl;
	}
///////////////////////////////////////////////////////////////////////////////


	
///////////////////////////////////////////////////////////////////////////////
/// Declaration of the TGraph                                               ///
///////////////////////////////////////////////////////////////////////////////

  /// BULK NUMBER OF EVENTS ///
	TGraph *gr_min_bulk    = new TGraph(n,x,ymin_bulk);
	TGraph *gr_max_bulk    = new TGraph(n,x,ymax_bulk);
	TGraph *gr_center_bulk = new TGraph(n,x,y_bulk);
	TGraph *gr_cl_bulk     = new TGraph(2*n);
	
	/// SURFACE NUMBER OF EVENTS ///
	TGraph *gr_min_surface    = new TGraph(n,x,ymin_surface);
	TGraph *gr_max_surface    = new TGraph(n,x,ymax_surface);
	TGraph *gr_center_surface = new TGraph(n,x,y_surface);
	TGraph *gr_cl_surface     = new TGraph(2*n);
	
	/// TRACKER NUMBER OF EVENTS ///
	TGraph *gr_min_tracker    = new TGraph(n,x,ymin_tracker);
	TGraph *gr_max_tracker    = new TGraph(n,x,ymax_tracker);
	TGraph *gr_center_tracker = new TGraph(n,x,y_tracker);
	TGraph *gr_cl_tracker     = new TGraph(2*n);
	
	/// BULK RELATIVE ERROR ///
	TGraph * gr_relative_error_tracker = new TGraph(n,x,relative_error_tracker);

	for (i=0;i<n;i++)  {
	
		gr_cl_bulk->SetPoint(i,x[i],ymax_bulk[i]);
		gr_cl_bulk->SetPoint(n+i,x[n-i-1],ymin_bulk[n-i-1]);
		gr_cl_tracker->SetPoint(i,x[i],ymax_tracker[i]);
		gr_cl_tracker->SetPoint(n+i,x[n-i-1],ymin_tracker[n-i-1]);
		gr_cl_surface->SetPoint(i,x[i],ymax_surface[i]);
		gr_cl_surface->SetPoint(n+i,x[n-i-1],ymin_surface[n-i-1]);
		
		gr_relative_error_tracker->SetPoint(n+i,x[n-i-1],relative_error_tracker[n-i-1]);
	}
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
/// OUTPUT                                                                  ///
///////////////////////////////////////////////////////////////////////////////

	/// BULK NUMBER OF EVENTS CANVAS ///
	canvas_bulk->cd();
	gr_cl_bulk->SetFillStyle(1001);
	gr_cl_bulk->SetFillColor(5);
	gr_cl_bulk->Draw("f");
	gr_min_bulk->Draw("l");
	gr_max_bulk->Draw("l");
	gr_center_bulk->SetLineWidth(1);
	gr_center_bulk->SetLineColor(1);
	gr_center_bulk->SetLineStyle(2);
	gr_center_bulk->SetMarkerColor(1);
	gr_center_bulk->SetMarkerStyle(8);
	gr_center_bulk->Draw("PC");
	gr_center_bulk->GetXaxis()->SetTitle("Time of exposure [days]");
	
	/// SURFACE NUMBER OF EVENTS CANVAS ///
	canvas_surface->cd();
	gr_cl_surface->SetFillStyle(1001);
	gr_cl_surface->SetFillColor(5);
	gr_cl_surface->Draw("f");
	gr_min_surface->Draw("l");
	gr_max_surface->Draw("l");
	gr_center_surface->SetLineWidth(1);
	gr_center_surface->SetLineColor(1);
	gr_center_surface->SetLineStyle(2);
	gr_center_surface->SetMarkerColor(1);
	gr_center_surface->SetMarkerStyle(8);
	gr_center_surface->Draw("PC");
	
	/// TRACKER NUMBER OF EVENTS CANVAS ///
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

