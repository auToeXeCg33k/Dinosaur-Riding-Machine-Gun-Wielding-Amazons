package commands;

import core.World;
import entities.Amazon;
import entities.Dinoszaurusz;
import items.Item;

public class LookAround implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D)
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                String string = "";
                for (Amazon amazon : world.getTiles()[i][j].getAmazonSet()) {
                  if (amazon != ((Select)world.getCommandMap().get("select")).getSelection())
                    string = string.concat("" + amazon + amazon + ", "); 
                } 
                for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j].getDinoszauruszList())
                  string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                for (Item item : world.getTiles()[i][j].getItemList())
                  string = string.concat("" + item + ", "); 
                if (string.equals("")) {
                  System.out.println("Az aktuális csempén nincs semmi.");
                } else {
                  System.out.println("Az aktuális csempén: " + string.substring(0, string.length() - 2) + ".");
                  string = "";
                } 
                if (i + 1 < world.getX()) {
                  for (Amazon amazon : world.getTiles()[i + 1][j].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i + 1][j].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Délre" : "Északra") + " nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Délre: " : "Északra: ") + (world.getActivePlayer() ? "Délre: " : "Északra: ") + ".");
                    string = "";
                  } 
                } 
                if (i + 1 < world.getX() && j + 1 < world.getY()) {
                  for (Amazon amazon : world.getTiles()[i + 1][j + 1].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j + 1].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i + 1][j + 1].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Dél-nyugatra " : "Észak-keletre ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Dél-nyugatra: " : "Észak-keletre: ") + (world.getActivePlayer() ? "Dél-nyugatra: " : "Észak-keletre: ") + ".");
                    string = "";
                  } 
                } 
                if (j + 1 < world.getY()) {
                  for (Amazon amazon : world.getTiles()[i][j + 1].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j + 1].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i][j + 1].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Nyugatra " : "Keletre ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Nyugatra: " : "Keletre: ") + (world.getActivePlayer() ? "Nyugatra: " : "Keletre: ") + ".");
                    string = "";
                  } 
                } 
                if (i - 1 >= 0 && j + 1 < world.getY()) {
                  for (Amazon amazon : world.getTiles()[i - 1][j + 1].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j + 1].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i - 1][j + 1].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Észak-nyugatra " : "Dél-keletre ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Észak-nyugatra: " : "Dél-keletre: ") + (world.getActivePlayer() ? "Észak-nyugatra: " : "Dél-keletre: ") + ".");
                    string = "";
                  } 
                } 
                if (i - 1 >= 0) {
                  for (Amazon amazon : world.getTiles()[i - 1][j].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i - 1][j].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Északra " : "Délre ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Északra: " : "Délre: ") + (world.getActivePlayer() ? "Északra: " : "Délre: ") + ".");
                    string = "";
                  } 
                } 
                if (i - 1 >= 0 && j - 1 >= 0) {
                  for (Amazon amazon : world.getTiles()[i - 1][j - 1].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j - 1].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i - 1][j - 1].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Észak-keletre " : "Dél-nyugatra ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Észak-keletre: " : "Dél-nyugatra: ") + (world.getActivePlayer() ? "Észak-keletre: " : "Dél-nyugatra: ") + ".");
                    string = "";
                  } 
                } 
                if (j - 1 >= 0) {
                  for (Amazon amazon : world.getTiles()[i][j - 1].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j - 1].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i][j - 1].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Keletre " : "Nyugatra ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Keletre: " : "Nyugatra: ") + (world.getActivePlayer() ? "Keletre: " : "Nyugatra: ") + ".");
                    string = "";
                  } 
                } 
                if (i + 1 < world.getX() && j - 1 >= 0) {
                  for (Amazon amazon : world.getTiles()[i + 1][j - 1].getAmazonSet())
                    string = string.concat("" + amazon + amazon + ", "); 
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j - 1].getDinoszauruszList())
                    string = string.concat("" + dinoszaurusz + dinoszaurusz + ", "); 
                  for (Item item : world.getTiles()[i + 1][j - 1].getItemList())
                    string = string.concat("" + item + ", "); 
                  if (string.equals("")) {
                    System.out.println((world.getActivePlayer() ? "Dél-keletre " : "Észak-nyugatra ") + "nincs semmi.");
                  } else {
                    System.out.println((world.getActivePlayer() ? "Dél-keletre: " : "Észak-nyugatra: ") + (world.getActivePlayer() ? "Dél-keletre: " : "Észak-nyugatra: ") + ".");
                  } 
                } 
                System.out.println();
                return;
              } 
            } 
          }  
        System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " nem is él!\n");
        return;
      } 
      System.out.println("Válasszá ki valakit!\n");
      return;
    } 
    System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
  }
}
