public class GetOff implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).isSelected())
        if (((Select)world.getCommandMap().get("select")).getSelection() instanceof Amazon) {
          if (((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getDinoszaurusz() != null) {
            if (((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getDinoszaurusz().isAlive()) {
              ((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).setLovagol(false);
              System.out.println(((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " leszállt " + ((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " dinoszauruszról.");
            } else {
              System.out.println(((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " dinoszaurusza nem él. hullákról már nem nagyon lehet hogy leszállni dik");
            } 
          } else {
            System.out.println(((Amazon)((Select)world.getCommandMap().get("select")).getSelection()).getNev() + " amazonnak nincs dínója. idomíts be vele egyet!");
          } 
        } else {
          System.out.println("csak amazonok tudnak leszállni dínókról bruh");
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
