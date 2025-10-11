// side by side

// std
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

// root
#include <TFile.h>
#include <TTree.h>

// gitlib
#include <argparse/argparse.hpp>

// mylib
#include "Mille.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[])
{
  // ArgParse
  argparse::ArgumentParser program("mille", "1.0");
  program.add_argument("-o", "--output")
      .help("specify the output file.")
      .required();
  program.add_argument("-i", "--input")
      .help("specify the input directory.")
      .required();
  program.add_argument("-t", "--text")
      .help("output data as text.")
      .flag();
  program.add_argument("-z", "--zero")
      .help("write zero data.")
      .flag();
  try
  {
    program.parse_args(argc, argv);
  }
  catch (const std::exception &err)
  {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    std::exit(1);
  }
  bool text = program.get<bool>("--text");
  bool zero = program.get<bool>("--zero");
  string input = program.get<string>("--input");
  string output = program.get<string>("--output");
  if (text)
  {
    output += ".txt";
  }
  else
  {
    output += ".bin";
  }

  // data23
  Mille mille_file(output.c_str(), !text, zero);
  // data22
  // TFile* f1=new TFile("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/8023_8025_8115_8301_8730_9073/kfalignment_data_iter5_noIFT_noZ.root");
  // Mille mille_file("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/8023_8025_8115_8301_8730_9073/mp2input.bin");
  // MC
  // TFile* f1=new TFile("/afs/cern.ch/user/k/keli/work/FASER/test/kfalignment_mc_0.root");
  // TFile* f1=new TFile("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/misalign_MC/kfalignment_mc_iter1_2ndf.root");
  // TFile* f1=new TFile("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/misalign_MC/kfalignment_mc_iter3.root");
  // TFile* f1=new TFile("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/misalign_MC/inputformp2.root");
  // TFile* f1=new TFile("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/misalign_MC/inputformp2_iter0.root");
  // Mille mille_file("/afs/cern.ch/user/k/keli/eos/Faser/alignment/global/misalign_MC/mp2input.bin");
  int Nfile = 48;

  for (int fileId = 0; fileId < Nfile; fileId++)
  {
    cout << "Dealing with File " << fileId << " ..." << endl;
    // if(fileId==29)continue;
    // if(fileId==14)continue;
    // if(fileId==31)continue;
    // if(fileId==40)continue;
    string InputFileName = input + "/kfalignment_010738_" + std::to_string(fileId) + ".root";
    // string InputFileName="/afs/cern.ch/user/t/tarai/run/result/kfalignment_010738_"+std::to_string(fileId)+".root";
    TFile *f1 = new TFile(InputFileName.c_str());
    TTree *t1 = (TTree *)f1->Get("trackParam");

    // 用来控制 Track 中对 Hits 循环的条件表达式的选择
    bool dump6ndf_modules = false;
    bool dumplayers = true;
    bool dump6ndf_layers = true;
    bool dumpz_layers = false;
    bool dumpstations = false;
    bool dump6ndf_stations = true;
    bool use_sidebyside = true;

    // 存储 28 个 branches
    double m_fitParam_x = 0;
    double m_fitParam_y = 0;
    double m_fitParam_chi2 = 0;
    double m_fitParam_px = 0;
    double m_fitParam_py = 0;
    double m_fitParam_pz = 0;
    double m_fitParam_charge = 0;
    std::vector<double> *m_fitParam_align_global_derivation_y_x = 0;
    std::vector<double> *m_fitParam_align_global_derivation_y_y = 0;
    std::vector<double> *m_fitParam_align_global_derivation_y_z = 0;
    std::vector<double> *m_fitParam_align_global_derivation_y_rx = 0;
    std::vector<double> *m_fitParam_align_global_derivation_y_ry = 0;
    std::vector<double> *m_fitParam_align_global_derivation_y_rz = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_x = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_y = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_z = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_rx = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_ry = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_rz = 0;
    std::vector<double> *m_fitParam_align_local_residual_x = 0;
    std::vector<double> *m_fitParam_align_local_measured_x = 0;
    std::vector<double> *m_fitParam_align_local_measured_xe = 0;
    std::vector<double> *m_fitParam_align_id = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_par_x = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_par_y = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_par_theta = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_par_phi = 0;
    std::vector<double> *m_fitParam_align_local_derivation_x_par_qop = 0;
    t1->SetBranchAddress("fitParam_x", &m_fitParam_x);
    t1->SetBranchAddress("fitParam_y", &m_fitParam_y);
    t1->SetBranchAddress("fitParam_chi2", &m_fitParam_chi2);
    t1->SetBranchAddress("fitParam_px", &m_fitParam_px);
    t1->SetBranchAddress("fitParam_py", &m_fitParam_py);
    t1->SetBranchAddress("fitParam_pz", &m_fitParam_pz);
    t1->SetBranchAddress("fitParam_charge", &m_fitParam_charge);
    t1->SetBranchAddress("fitParam_align_global_derivation_y_x", &m_fitParam_align_global_derivation_y_x);
    t1->SetBranchAddress("fitParam_align_global_derivation_y_y", &m_fitParam_align_global_derivation_y_y);
    t1->SetBranchAddress("fitParam_align_global_derivation_y_z", &m_fitParam_align_global_derivation_y_z);
    t1->SetBranchAddress("fitParam_align_global_derivation_y_rx", &m_fitParam_align_global_derivation_y_rx);
    t1->SetBranchAddress("fitParam_align_global_derivation_y_ry", &m_fitParam_align_global_derivation_y_ry);
    t1->SetBranchAddress("fitParam_align_global_derivation_y_rz", &m_fitParam_align_global_derivation_y_rz);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_x", &m_fitParam_align_local_derivation_x_x);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_y", &m_fitParam_align_local_derivation_x_y);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_z", &m_fitParam_align_local_derivation_x_z);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_rx", &m_fitParam_align_local_derivation_x_rx);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_ry", &m_fitParam_align_local_derivation_x_ry);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_rz", &m_fitParam_align_local_derivation_x_rz);
    t1->SetBranchAddress("fitParam_align_local_residual_x", &m_fitParam_align_local_residual_x);
    t1->SetBranchAddress("fitParam_align_local_measured_x", &m_fitParam_align_local_measured_x);
    t1->SetBranchAddress("fitParam_align_local_measured_xe", &m_fitParam_align_local_measured_xe);
    t1->SetBranchAddress("fitParam_align_id", &m_fitParam_align_id);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_par_x", &m_fitParam_align_local_derivation_x_par_x);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_par_y", &m_fitParam_align_local_derivation_x_par_y);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_par_theta", &m_fitParam_align_local_derivation_x_par_theta);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_par_phi", &m_fitParam_align_local_derivation_x_par_phi);
    t1->SetBranchAddress("fitParam_align_local_derivation_x_par_qop", &m_fitParam_align_local_derivation_x_par_qop);

    int nevt = t1->GetEntries();

    // loop over all the events
    std::vector<int> labels;
    std::vector<float> glo_der;
    std::vector<float> loc_der;
    float resi = 0.;
    float resi_e = 0.;
    bool diffside = false;

    int ioutput = 0;
    int nhits[8] = {0};
    for (int ievt = 0; ievt < nevt; ++ievt)
    {
      t1->GetEntry(ievt);
      // std::cout<<"like "<<ievt<<" "<<m_fitParam_chi2/m_fitParam_ndf<<" "<<m_fitParam_pz<<" "<<m_fitParam_align_id->size()<<std::endl;
      if (m_fitParam_chi2 > 2000 || m_fitParam_pz < 100 || m_fitParam_pz > 5000 || m_fitParam_align_id->size() < 15)
        continue;
      // if(m_fitParam_chi2>500||m_fitParam_pz<100||m_fitParam_pz>5000||m_fitParam_align_id->size()<15)continue;
      ++ioutput;
      //    if(ioutput>1000)continue;

      // loop over one track
      for (int ihit = 0; ihit < m_fitParam_align_id->size(); ++ihit)
      {
        labels.clear();
        glo_der.clear();
        loc_der.clear();
        if (fabs(m_fitParam_align_local_residual_x->at(ihit)) > 0.05)
          continue;
        if (m_fitParam_align_local_derivation_x_x->at(ihit) < -9000 || m_fitParam_align_local_derivation_x_rz->at(ihit) < -9000 || m_fitParam_align_global_derivation_y_x->at(ihit) < -9000 || m_fitParam_align_global_derivation_y_y->at(ihit) < -9000 || m_fitParam_align_global_derivation_y_z->at(ihit) < -9000 || m_fitParam_align_global_derivation_y_rx->at(ihit) < -9000 || m_fitParam_align_global_derivation_y_ry->at(ihit) < -9000 || m_fitParam_align_global_derivation_y_rz->at(ihit) < -9000)
          continue;

        int moduleid = m_fitParam_align_id->at(ihit);

        diffside = false;
        // if((moduleid%10==1)&&(!use_sidebyside)) --moduleid;
        moduleid += 1000; // station from 1 not 0

        //	int layerid = moduleid/100;
        //	if(moduleid/100==10){
        //	  if(nhits[moduleid%100/10]>1000)continue;
        //	  nhits[moduleid%100/10]+=1;
        //	}

        // if(dump6ndf_modules)
        // {
        //   if(use_sidebyside)
        //   {
        //     labels.push_back(moduleid*10+0+1);//millepede can not have label at 0
        //     labels.push_back(moduleid*10+1+1);
        //     glo_der.push_back(m_fitParam_align_local_derivation_x_x->at(ihit));
        //     glo_der.push_back(m_fitParam_align_local_derivation_x_y->at(ihit));
        //   }
        //   else
        //   {
        //     labels.push_back(moduleid*10+0+1);//millepede can not have label at 0
        //     glo_der.push_back(m_fitParam_align_local_derivation_x_x->at(ihit));
        //   }

        //   labels.push_back(moduleid*10+2+1);
        //   labels.push_back(moduleid*10+3+1);
        //   labels.push_back(moduleid*10+4+1);
        //   labels.push_back(moduleid*10+5+1);
        //   glo_der.push_back(m_fitParam_align_local_derivation_x_z->at(ihit));
        //   glo_der.push_back(m_fitParam_align_local_derivation_x_rx->at(ihit));
        //   glo_der.push_back(m_fitParam_align_local_derivation_x_ry->at(ihit));
        //   glo_der.push_back(m_fitParam_align_local_derivation_x_rz->at(ihit));
        // }
        // else
        {
          labels.push_back(moduleid * 10 + 0 + 1); // millepede can not have label at 0
          labels.push_back(((moduleid / 10) * 10) * 10 + 1 + 1);
          glo_der.push_back(m_fitParam_align_local_derivation_x_x->at(ihit));
          glo_der.push_back(m_fitParam_align_local_derivation_x_rz->at(ihit));
        }

        if (dumplayers)
        {
          int layerid = moduleid / 100;
          //	std::cout<<"id "<<moduleid<<" "<<layerid<<std::endl;
          if (dump6ndf_layers)
          {
            if (fabs(m_fitParam_align_global_derivation_y_rx->at(ihit)) > 2 || fabs(m_fitParam_align_global_derivation_y_ry->at(ihit)) > 2)
              continue;
            labels.push_back(layerid * 10 + 0 + 1); // millepede can not have label at 0
            labels.push_back(layerid * 10 + 1 + 1);
            labels.push_back(layerid * 10 + 2 + 1);
            labels.push_back(layerid * 10 + 3 + 1);
            labels.push_back(layerid * 10 + 4 + 1);
            glo_der.push_back(m_fitParam_align_global_derivation_y_x->at(ihit));
            glo_der.push_back(m_fitParam_align_global_derivation_y_y->at(ihit));
            // if(dumpz_layers)
            // {
            //   labels.push_back(layerid*10+5+1);
            //   glo_der.push_back(m_fitParam_align_global_derivation_y_z->at(ihit));
            // }
            glo_der.push_back(m_fitParam_align_global_derivation_y_rx->at(ihit));
            glo_der.push_back(m_fitParam_align_global_derivation_y_ry->at(ihit));
            glo_der.push_back(m_fitParam_align_global_derivation_y_rz->at(ihit));
          }
          // else
          // {
          //   labels.push_back(layerid*10+0+1);//millepede can not have label at 0
          //   labels.push_back(layerid*10+1+1);
          //   glo_der.push_back(m_fitParam_align_global_derivation_y_y->at(ihit));
          //   glo_der.push_back(m_fitParam_align_global_derivation_y_rz->at(ihit));
          // }
        }

        // if(dumpstations)
        // {
        //   int stationid = moduleid/1000;
        //   if(dump6ndf_stations)
        //   {
        //     labels.push_back(stationid*10+0+1);//millepede can not have label at 0
        //     labels.push_back(stationid*10+1+1);
        //     labels.push_back(stationid*10+2+1);
        //     labels.push_back(stationid*10+3+1);
        //     labels.push_back(stationid*10+4+1);
        //     labels.push_back(stationid*10+5+1);
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_x->at(ihit));
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_y->at(ihit));
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_z->at(ihit));
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_rx->at(ihit));
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_ry->at(ihit));
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_rz->at(ihit));
        //   }
        //   else
        //   {
        //     labels.push_back(stationid*10+0+1);//millepede can not have label at 0
        //     labels.push_back(stationid*10+1+1);
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_y->at(ihit));
        //     glo_der.push_back(m_fitParam_align_global_derivation_y_rz->at(ihit));
        //   }
        // }

        loc_der.push_back(m_fitParam_align_local_derivation_x_par_x->at(ihit));
        loc_der.push_back(m_fitParam_align_local_derivation_x_par_y->at(ihit));
        loc_der.push_back(m_fitParam_align_local_derivation_x_par_theta->at(ihit));
        loc_der.push_back(m_fitParam_align_local_derivation_x_par_phi->at(ihit));
        loc_der.push_back(m_fitParam_align_local_derivation_x_par_qop->at(ihit));
        // std::cout<<"like "<<ievt<<" "<<ihit<<" "<<loc_der.size()<<std::endl;
        float *lcder = loc_der.data();
        float *glder = glo_der.data();
        int *label = labels.data();
        resi = m_fitParam_align_local_residual_x->at(ihit);
        resi_e = m_fitParam_align_local_measured_xe->at(ihit);
        mille_file.mille(loc_der.size(), lcder, glo_der.size(), glder, label, resi, resi_e);
      }
      mille_file.end();
      // mille_file.flushTrack();
    }
  }
  mille_file.kill();
}
