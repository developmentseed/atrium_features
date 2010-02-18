<div class='atrium-welcome'>
  <?php print $content ?>

  <?php if (!empty($columns)): ?>
  <div class='atrium-welcome-links clear-block'>
    <?php foreach ($columns as $column): ?>
      <div class='column'>
        <?php foreach ($column as $link): ?>
        <?php print l($link['title'], $link['href'], array('html' => TRUE)) ?>
        <?php endforeach; ?>
      </div>
    <?php endforeach; ?>
  </div>
  <?php endif; ?>

  <?php if (!empty($admin)): ?>
  <div class='description'>
    <?php print $admin ?>
  </div>
  <?php endif; ?>
</div>