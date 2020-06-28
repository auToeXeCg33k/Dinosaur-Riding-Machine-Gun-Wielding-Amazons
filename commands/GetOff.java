package commands;

import core.World;

public class GetOff implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null) {
            if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().getHP() > 0.0D) {
              ((Select)world.getCommandMap().get("select")).getSelection().setLovagol(false);
              System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " leszállt a dinoszauruszról.\n");
              return;
            } 
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " dinoszaurusza nem él. Hullákról már nem nagyon lehet hogy leszállni dik...\n");
            return;
          } 
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak nincs dínója. Idomíts be vele egyet!\n");
          return;
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
