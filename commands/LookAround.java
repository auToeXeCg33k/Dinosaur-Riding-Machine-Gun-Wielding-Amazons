package commands;

import core.Player;
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
                System.out.print("Amazonok az aktuális koordinátán: ");
                for (Amazon amazon : world.getTiles()[i][j].getAmazonSet()) {
                  if (amazon != ((Select)world.getCommandMap().get("select")).getSelection())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                } 
                System.out.print("\nDinoszauruszok az aktuális koordinátán: ");
                for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j].getDinoszauruszList()) {
                  if (dinoszaurusz != ((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz())
                    System.out.print("" + dinoszaurusz + " "); 
                } 
                System.out.print("\nItemek az aktuális koordinátán: ");
                for (Item item : world.getTiles()[i][j].getItemList()) {
                  if (item != ((Select)world.getCommandMap().get("select")).getSelection().getGepFegyver())
                    System.out.print("" + item + " "); 
                } 
                if (i + 1 < world.getX()) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "délre: " : "északra: "));
                  for (Amazon amazon : world.getTiles()[i + 1][j].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "délre: " : "északra: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "délre: " : "északra: "));
                  for (Item item : world.getTiles()[i + 1][j].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (i + 1 < world.getX() && j + 1 < world.getY()) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "dél-nyugatra: " : "észak-keletre: "));
                  for (Amazon amazon : world.getTiles()[i + 1][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "dél-nyugatra: " : "észak-keletre: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j + 1].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "dél-nyugatra: " : "észak-keletre: "));
                  for (Item item : world.getTiles()[i + 1][j + 1].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (j + 1 < world.getY()) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "nyugatra: " : "keletre: "));
                  for (Amazon amazon : world.getTiles()[i][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "nyugatra: " : "keletre: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j + 1].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "nyugatra: " : "keletre: "));
                  for (Item item : world.getTiles()[i][j + 1].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (i - 1 >= 0 && j + 1 < world.getY()) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "észak-nyugatra: " : "dél-keletre: "));
                  for (Amazon amazon : world.getTiles()[i - 1][j + 1].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "észak-nyugatra: " : "dél-keletre: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j + 1].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "észak-nyugatra: " : "dél-keletre: "));
                  for (Item item : world.getTiles()[i - 1][j + 1].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (i - 1 >= 0) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "északra: " : "délre: "));
                  for (Amazon amazon : world.getTiles()[i - 1][j].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "északra: " : "délre: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "északra: " : "délre: "));
                  for (Item item : world.getTiles()[i - 1][j].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (i - 1 >= 0 && j - 1 >= 0) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "észak-keletre: " : "dél-nyugatra: "));
                  for (Amazon amazon : world.getTiles()[i - 1][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "észak-keletre: " : "dél-nyugatra: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i - 1][j - 1].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "észak-keletre: " : "dél-nyugatra: "));
                  for (Item item : world.getTiles()[i - 1][j - 1].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (j - 1 >= 0) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "keletre: " : "nyugatra: "));
                  for (Amazon amazon : world.getTiles()[i][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "keletre: " : "nyugatra: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i][j - 1].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "keletre: " : "nyugatra: "));
                  for (Item item : world.getTiles()[i][j - 1].getItemList())
                    System.out.print("" + item + " "); 
                } 
                if (i + 1 < world.getX() && j - 1 >= 0) {
                  System.out.print("\nAmazonok " + (world.getActivePlayer() ? "dél-keletre:" : "észak-nyugatra: "));
                  for (Amazon amazon : world.getTiles()[i + 1][j - 1].getAmazonSet())
                    System.out.print(amazon.getNev() + "(" + amazon.getNev() + ", " + (((Player)world.getPlayerMap().get(Boolean.valueOf(world.getActivePlayer()))).hasAmazon(amazon) ? "friendly" : "enemy")); 
                  System.out.print("\nDinoszauruszok " + (world.getActivePlayer() ? "dél-keletre:" : "észak-nyugatra: "));
                  for (Dinoszaurusz dinoszaurusz : world.getTiles()[i + 1][j - 1].getDinoszauruszList())
                    System.out.print("" + dinoszaurusz + " "); 
                  System.out.print("\nItemek " + (world.getActivePlayer() ? "dél-keletre:" : "észak-nyugatra: "));
                  for (Item item : world.getTiles()[i + 1][j - 1].getItemList())
                    System.out.print("" + item + " "); 
                } 
                System.out.println("\n");
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
