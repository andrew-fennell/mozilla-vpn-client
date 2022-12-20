(function(api, condition) {
  //Show message only if within 1 week of expiring.
  let weekBeforeExpireSecs = (api.subscriptionData.expiresOn / 1000) - 7*24*60*60;
  if (Date.now() < api.subscriptionData.expiresOn && 
      Date.now() > weekBeforeExpireSecs*1000) {
    api.addon.date = weekBeforeExpireSecs;
    condition.enable();    
  } else {
    condition.disable();        
  }
})
