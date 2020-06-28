public class GetOn implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 1) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz() != null) {
          if (((Select)world.getCommandMap().get("select")).getSelection().getDinoszaurusz().isAlive()) {
            ((Select)world.getCommandMap().get("select")).getSelection().setLovagol(true);
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " felszállt " + ((Select)world.getCommandMap().get("select")).getSelection().getNev() + " dinoszauruszra.");
          } else {
            System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " dinoszaurusza nem él. hullákra nem szállunk fel more");
          } 
        } else {
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak nincs dínója. idomíts be vele egyet!");
        } 
      } else {
        System.out.println("válasszá valakit");
      } 
    } else {
      System.out.println("nem megfelelő argumentumszám");
    } 
  }
  
  public boolean execute() {
    return false;
  }
}
