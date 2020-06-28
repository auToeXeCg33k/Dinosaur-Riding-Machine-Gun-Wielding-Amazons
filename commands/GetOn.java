package commands;

import core.World;

public class GetOn implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null)
            for (int i = 0; i < (world.getTiles()).length; i++) {
              for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                  if (world.getTiles()[i][j].containsDinoszaurusz(((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz())) {
                    if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().getHP() > 0.0D) {
                      ((Select)world.getCommandMap().get("select")).getSelection().setLovagol(true);
                      System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " felszállt a dinoszauruszra.\n");
                      return;
                    } 
                    System.out.println("A dínó ki van múlva.\n");
                    return;
                  } 
                  System.out.println("Nincs itt a dínó.\n");
                  return;
                } 
              } 
            }  
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak nincs dínója. Idomíts be vele egyet!\n");
          return;
        } 
        System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " nem is él!\n");
        return;
      } 
      System.out.println("Válasszá valakit!\n");
      return;
    } 
    System.out.println("Nem megfelelö a gyökérségek száma heló!\n");
  }
}
