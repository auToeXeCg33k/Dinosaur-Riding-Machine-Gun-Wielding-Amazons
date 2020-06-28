package commands;

import core.Data;
import entities.Amazon;
import entities.Dinoszaurusz;
import items.Item;
import units.Point;
import units.Report;

public class LookAround implements Command {
  public Report execute(String[] strs, Data data) {
    if (strs.length != 1)
      return new Report("Nem megfelelő a gyökérségek száma heló!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection() == null)
      return new Report("Válasszá ki valakit!\n", false); 
    if (((Select)data.getCommands().get("select")).getSelection().getHP() == 0.0D)
      return new Report(((Select)data.getCommands().get("select")).getSelection().getNev() + " nem is él!\n", false); 
    Point p = data.location(((Select)data.getCommands().get("select")).getSelection());
    String ret = "";
    String temp = "";
    if (data.getWorld().getTiles()[p.getY()][p.getX()].contains())
      temp = temp.concat("BRAINDRAINER, "); 
    for (Amazon amazon : data.getWorld().getTiles()[p.getY()][p.getX()].getAmazonSet()) {
      if (amazon != ((Select)data.getCommands().get("select")).getSelection())
        temp = temp.concat("" + amazon + amazon + ", "); 
    } 
    for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY()][p.getX()].getDinoszauruszList())
      temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
    for (Item item : data.getWorld().getTiles()[p.getY()][p.getX()].getItemList())
      temp = temp.concat("" + item + ", "); 
    if (temp.equals("")) {
      ret = ret.concat("Az aktuális mezőn nincs semmi.\n");
    } else {
      ret = ret.concat("Az aktuális mezőn: " + temp.substring(0, temp.length() - 2) + ".\n");
      temp = "";
    } 
    if (p.getY() + 1 < data.getWorld().getSize()) {
      if (data.getWorld().getTiles()[p.getY() + 1][p.getX()].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY() + 1][p.getX()].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY() + 1][p.getX()].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY() + 1][p.getX()].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Délre" : "Északra") + " nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Délre: " : "Északra: ") + (data.getPlayerMarker() ? "Délre: " : "Északra: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getY() + 1 < data.getWorld().getSize() && p.getX() + 1 < data.getWorld().getSize()) {
      if (data.getWorld().getTiles()[p.getY() + 1][p.getX() + 1].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY() + 1][p.getX() + 1].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY() + 1][p.getX() + 1].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY() + 1][p.getX() + 1].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Dél-nyugatra " : "Észak-keletre ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Dél-nyugatra: " : "Észak-keletre: ") + (data.getPlayerMarker() ? "Dél-nyugatra: " : "Észak-keletre: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getX() + 1 < data.getWorld().getSize()) {
      if (data.getWorld().getTiles()[p.getY()][p.getX() + 1].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY()][p.getX() + 1].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY()][p.getX() + 1].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY()][p.getX() + 1].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Nyugatra " : "Keletre ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Nyugatra: " : "Keletre: ") + (data.getPlayerMarker() ? "Nyugatra: " : "Keletre: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getY() - 1 >= 0 && p.getX() + 1 < data.getWorld().getSize()) {
      if (data.getWorld().getTiles()[p.getY() - 1][p.getX() + 1].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY() - 1][p.getX() + 1].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY() - 1][p.getX() + 1].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY() - 1][p.getX() + 1].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Észak-nyugatra " : "Dél-keletre ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Észak-nyugatra: " : "Dél-keletre: ") + (data.getPlayerMarker() ? "Észak-nyugatra: " : "Dél-keletre: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getY() - 1 >= 0) {
      if (data.getWorld().getTiles()[p.getY() - 1][p.getX()].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY() - 1][p.getX()].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY() - 1][p.getX()].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY() - 1][p.getX()].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Északra " : "Délre ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Északra: " : "Délre: ") + (data.getPlayerMarker() ? "Északra: " : "Délre: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getY() - 1 >= 0 && p.getX() - 1 >= 0) {
      if (data.getWorld().getTiles()[p.getY() - 1][p.getX() - 1].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY() - 1][p.getX() - 1].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY() - 1][p.getX() - 1].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY() - 1][p.getX() - 1].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Észak-keletre " : "Dél-nyugatra ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Észak-keletre: " : "Dél-nyugatra: ") + (data.getPlayerMarker() ? "Észak-keletre: " : "Dél-nyugatra: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getX() - 1 >= 0) {
      if (data.getWorld().getTiles()[p.getY()][p.getX() - 1].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY()][p.getX() - 1].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY()][p.getX() - 1].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY()][p.getX() - 1].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Keletre " : "Nyugatra ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Keletre: " : "Nyugatra: ") + (data.getPlayerMarker() ? "Keletre: " : "Nyugatra: ") + ".\n");
        temp = "";
      } 
    } 
    if (p.getY() + 1 < data.getWorld().getSize() && p.getX() - 1 >= 0) {
      if (data.getWorld().getTiles()[p.getY() + 1][p.getX() - 1].contains())
        temp = temp.concat("BRAINDRAINER, "); 
      for (Amazon amazon : data.getWorld().getTiles()[p.getY() + 1][p.getX() - 1].getAmazonSet())
        temp = temp.concat("" + amazon + amazon + ", "); 
      for (Dinoszaurusz dinoszaurusz : data.getWorld().getTiles()[p.getY() + 1][p.getX() - 1].getDinoszauruszList())
        temp = temp.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
      for (Item item : data.getWorld().getTiles()[p.getY() + 1][p.getX() - 1].getItemList())
        temp = temp.concat("" + item + ", "); 
      if (temp.equals("")) {
        ret = ret.concat((data.getPlayerMarker() ? "Dél-keletre " : "Észak-nyugatra ") + "nincs semmi.\n");
      } else {
        ret = ret.concat((data.getPlayerMarker() ? "Dél-keletre: " : "Észak-nyugatra: ") + (data.getPlayerMarker() ? "Dél-keletre: " : "Észak-nyugatra: ") + ".\n");
      } 
    } 
    return new Report(ret, false);
  }
}
