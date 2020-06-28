public class GetOff implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null)
        if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().isAlive()) {
            ((Select)world.getCommandMap().get("select")).getSelection().setLovagol(false);
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " leszállt a dinoszauruszról.");
          } else {
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " dinoszaurusza nem él. hullákról már nem nagyon lehet hogy leszállni dik");
          } 
        } else {
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak nincs dínója. idomíts be vele egyet!");
        }  
      System.out.println("válasszá ki valakit");
    } else {
      System.out.println("nem megfelelő argumentumszám");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
