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
                      System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " felszállt a dinoszauruszra.");
                      return;
                    } 
                    System.out.println("a dínó ki van múlva");
                    return;
                  } 
                  System.out.println("nincs itt a dínó");
                  return;
                } 
              } 
            }  
          System.out.println(((Select)world.getCommandMap().get("select")).getSelection().getNev() + " amazonnak nincs dínója. idomíts be vele egyet!");
          return;
        } 
        System.out.println("A kiválasztott amazon nem is él.");
        return;
      } 
      System.out.println("válasszá valakit");
      return;
    } 
    System.out.println("nem megfelelő argumentumszám");
  }
  
  public boolean execute() {
    return false;
  }
}
