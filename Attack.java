class Attack implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (((Select)world.getCommandMap().get("select")).getSelection().getHP() != 0.0D) {
          if (world.getAmazonMap().containsKey(strs[1]))
            for (int i = 0; i < (world.getTiles()).length; i++) {
              for (int j = 0; j < (world.getTiles()[0]).length; j++) {
                if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection())) {
                  if (world.getTiles()[i][j].containsAmazon(world.getAmazonMap().get(strs[1]))) {
                    if (((Amazon)world.getAmazonMap().get(strs[1])).getHP() != 0.0D) {
                      ((Select)world.getCommandMap().get("select")).getSelection().tamad(world.getAmazonMap().get(strs[1]));
                      return;
                    } 
                    System.out.println("a célzott amazon nem él");
                    return;
                  } 
                  System.out.println("az amazon nincs rangeben");
                  return;
                } 
              } 
            }  
          System.out.println("ilyen amazon nincs");
          return;
        } 
        System.out.println("A kiválasztott amazon nem is él");
        return;
      } 
      System.out.println("válasszá valami buzit");
      return;
    } 
    System.out.println("nem megfelelő argumentummennyiség");
  }
  
  public boolean execute() {
    return true;
  }
}
