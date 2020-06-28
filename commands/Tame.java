package commands;

import core.World;
import entities.Dinoszaurusz;
import java.util.Scanner;

public class Tame implements Command {
  public void execute(String[] strs, World world) {
    if (world.getMoveCounter() < world.getMaxCounter()) {
      if (strs.length == 1) {
        if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
            if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() == null)
              for (int i = 0; i < (world.getTiles()).length; i++) {
                for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                  if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                    switch (world.getTiles()[i][j].getDinoszauruszList().size()) {
                      case 0:
                        System.out.println("Nincs dínó a közelben.\n");
                        return;
                      case 1:
                        if (((Dinoszaurusz)world.getTiles()[i][j].getDinoszauruszList().get(0)).getTamed()) {
                          System.out.println("Ez a dínó mán másé.\n");
                          return;
                        } 
                        ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getTiles()[i][j].getDinoszauruszList().get(0));
                        System.out.println("Dínó beidomítva.\n");
                        world.incCounter();
                        return;
                    } 
                    for (int k = 0; k < world.getTiles()[i][j].getDinoszauruszList().size(); k++)
                      System.out.println("" + k + 1 + ": " + k + 1); 
                    System.out.print("Az idomítani kívánt dinoszaurusz száma: ");
                    Scanner sc = new Scanner(System.in);
                    String input = sc.nextLine();
                    String[] strings = input.split(" ");
                    if (strings.length == 1)
                      try {
                        int index = Integer.parseInt(strings[0]) - 1;
                        if (index < world.getTiles()[i][j].getDinoszauruszList().size() && index >= 0) {
                          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().getTamed()) {
                            System.out.println("Ez a dínó mán másé.\n");
                            return;
                          } 
                          ((Select)world.getCommandMap().get("select")).getSelection().tame(world.getTiles()[i][j].getDinoszauruszList().get(index));
                          System.out.println("Dínó beidomítva.\n");
                          world.incCounter();
                          return;
                        } 
                        System.out.println("Mi ez a szám more?\n");
                        return;
                      } catch (NumberFormatException e) {
                        System.out.println("Ez nem is szám baszod...\n");
                        return;
                      }  
                    System.out.println("Túl sok faszság...\n");
                    return;
                  } 
                } 
              }  
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak mán van dínója.\n");
            return;
          } 
          System.out.println("" + ((Select)world.getCommandMap().get("select")).getSelection() + " nem is él.\n");
          return;
        } 
        System.out.println("Válasszá ki valakit!\n");
        return;
      } 
      System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
      return;
    } 
    System.out.println("Nincs több lépésed.\n");
  }
}
