<script lang="ts">
  let { data } = $props();

  type Block =
    | { type: 'hero'; title: string; subtitle: string }
    | { type: 'card'; text: string };

  type PageData = {
    page: {
      page: string;
      title: string;
      subtitle: string;
      blocks: Block[];
    };
  };

  // FIX 1: Use $derived to ensure pageData updates if data changes
  let pageData = $derived((data as PageData).page);
</script>

<svelte:head>
  <title>{pageData.title}</title>
</svelte:head>

<div class="page">
  <h1>{pageData.title}</h1>
  <p>{pageData.subtitle}</p>

  <div class="grid">
    {#each pageData.blocks as block, i (i)}
      {#if block.type === 'hero'}
        <section class="hero">
          <h2>{block.title}</h2>
          <p>{block.subtitle}</p>
        </section>
      {:else if block.type === 'card'}
        <div class="card">{block.text}</div>
      {/if}
    {/each}
  </div>
</div>

<style>
  .page {
    min-height: 100vh;
    padding: 2rem;
    background: #0f1115;
    color: #f5f7fa;
    font-family: system-ui, sans-serif;
  }

  .grid {
    display: grid;
    gap: 1rem;
    margin-top: 1.5rem;
    grid-template-columns: repeat(auto-fit, minmax(220px, 1fr));
  }

  .hero, .card {
    background: #1a1f29;
    border-radius: 16px;
    padding: 1rem;
  }
</style>