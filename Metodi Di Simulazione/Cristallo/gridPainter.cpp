#include "squareGrid.h"
#include "gridPainter.h"
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

gridPainter::gridPainter(const squareGrid& grid) : _grid(grid) {
    // Constructor implementation can be extended if needed
}

void gridPainter::drawGrid() {
    int sideLength = _grid.sideLenght();
    _histogram = new TH2D("grid", " ", sideLength, 0, sideLength, sideLength, 0, sideLength);
    
    for (int x = 0; x < sideLength; ++x) {
        for (int y = 0; y < sideLength; ++y) {
            if (_grid.isCellFilled(x, y)) {
                _histogram->SetBinContent(x + 1, y + 1, 1); // Set filled cells to 1
            } else {
                _histogram->SetBinContent(x + 1, y + 1, 0); // Set empty cells to 0
            }
        }
    }

    _canvas = new TCanvas("canvas", "Square Grid Canvas", 800, 600);
    auto legend = new TLegend(0.35,1,0.65,0.9);
    legend->AddEntry((TObject*)nullptr, Form("Percentage Coverage: %.2f%%", _grid.percentageCoverage() * 100), "");
    legend->AddEntry((TObject*)nullptr, Form("Filled Cells: %d", _grid.filledCells()), "");
    _histogram->SetStats(0);
    _histogram->GetXaxis()->SetTickLength(-0.1);
    _histogram->GetYaxis()->SetTickLength(-0.1);
    gStyle->SetPalette(52);
    TColor::InvertPalette();
    _canvas->cd();    
    _histogram->Draw("COLZ"); // Draw the histogram with color
    legend->Draw();
    _canvas->Update(); // Update the canvas to reflect changes
}