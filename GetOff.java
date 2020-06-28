public class GetOff implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() > 0.0D) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null) {
            if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().getHP() > 0.0D) {
              ((Select)world.getCommandMap().get("select")).getSelection().setLovagol(false);
              System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " leszállt a dinoszauruszról.");
              return;
            } 
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " dinoszaurusza nem él. hullákról már nem nagyon lehet hogy leszállni dik");
            return;
          } 
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak nincs dínója. idomíts be vele egyet!");
          return;
        } 
        System.out.println("A kiválasztott amazon nem is él");
        return;
      } 
      System.out.println("válasszá ki valakit");
      return;
    } 
    System.out.println("nem megfelelő argumentumszám");
  }
  
  public boolean execute() {
    return false;
  }
}
