class Attack implements Command {
  public void execute(String[] strs, World world) {
    if (strs.length == 2) {
      if (((Select)world.getCommandMap().get("select")).getSelection() != null) {
        if (world.getAmazonMap().containsKey(strs[1])) {
          for (int i = 0; i < (world.getTiles()).length; i++) {
            for (int j = 0; j < (world.getTiles()[0]).length; j++) {
              if (world.getTiles()[i][j].containsAmazon(((Select)world.getCommandMap().get("select")).getSelection()))
                if (world.getTiles()[i][j].containsAmazon(world.getAmazonMap().get(strs[1]))) {
                  ((Select)world.getCommandMap().get("select")).getSelection().tamad(world.getAmazonMap().get(strs[1]));
                } else {
                  System.out.println("az amazon nincs rangeben");
                }  
            } 
          } 
        } else {
          System.out.println("ilyen amazon nincs");
        } 
      } else {
        System.out.println("válasszá valami buzit");
      } 
    } else {
      System.out.println("nem megfelelő argumentummennyiség");
    } 
  }
  
  public boolean execute() {
    return true;
  }
}
